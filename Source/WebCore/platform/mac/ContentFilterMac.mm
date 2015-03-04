/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "config.h"
#import "ContentFilter.h"

#if ENABLE(CONTENT_FILTERING)

#import "ResourceResponse.h"
#import "SoftLinking.h"
#import "WebFilterEvaluatorSPI.h"
#import <objc/runtime.h>

#if HAVE(NE_FILTER_SOURCE)
#import "NEFilterSourceSPI.h"
SOFT_LINK_FRAMEWORK(NetworkExtension);
SOFT_LINK_CLASS(NetworkExtension, NEFilterSource);
#endif

SOFT_LINK_PRIVATE_FRAMEWORK(WebContentAnalysis);
SOFT_LINK_CLASS(WebContentAnalysis, WebFilterEvaluator);

namespace WebCore {

ContentFilter::ContentFilter(const ResourceResponse& response)
#if HAVE(NE_FILTER_SOURCE)
    : m_neFilterSourceStatus(NEFilterSourceStatusNeedsMoreData)
    , m_neFilterSourceQueue(0)
#endif
{
    if ([getWebFilterEvaluatorClass() isManagedSession])
        m_platformContentFilter = adoptNS([allocWebFilterEvaluatorInstance() initWithResponse:response.nsURLResponse()]);

#if HAVE(NE_FILTER_SOURCE)
    if ([getNEFilterSourceClass() filterRequired]) {
        m_neFilterSource = adoptNS([allocNEFilterSourceInstance() initWithURL:[response.nsURLResponse() URL] direction:NEFilterSourceDirectionInbound socketIdentifier:0]);
        m_neFilterSourceQueue = dispatch_queue_create("com.apple.WebCore.NEFilterSourceQueue", DISPATCH_QUEUE_SERIAL);
        
        long long expectedContentSize = [response.nsURLResponse() expectedContentLength];
        if (expectedContentSize < 0)
            m_originalData = adoptNS([[NSMutableData alloc] init]);
        else
            m_originalData = adoptNS([[NSMutableData alloc] initWithCapacity:(NSUInteger)expectedContentSize]);
    }
#endif
}

ContentFilter::~ContentFilter()
{
#if HAVE(NE_FILTER_SOURCE)
    if (m_neFilterSourceQueue)
        dispatch_release(m_neFilterSourceQueue);
#endif
}

bool ContentFilter::canHandleResponse(const ResourceResponse& response)
{
    if (!response.url().protocolIsInHTTPFamily())
        return false;

    if ([getWebFilterEvaluatorClass() isManagedSession]) {
#if PLATFORM(MAC)
        if (response.url().protocolIs("https"))
#endif
            return true;
    }

#if HAVE(NE_FILTER_SOURCE)
    return [getNEFilterSourceClass() filterRequired];
#else
    return false;
#endif
}

void ContentFilter::addData(const char* data, int length)
{
    ASSERT(needsMoreData());

    if (m_platformContentFilter) {
        ASSERT(![m_replacementData.get() length]);
        m_replacementData = [m_platformContentFilter addData:[NSData dataWithBytesNoCopy:(void*)data length:length freeWhenDone:NO]];
        ASSERT(needsMoreData() || [m_replacementData.get() length]);
    }

#if HAVE(NE_FILTER_SOURCE)
    if (!m_neFilterSource)
        return;

    // FIXME: NEFilterSource doesn't buffer data like WebFilterEvaluator does,
    // so we need to do it ourselves so getReplacementData() can return the
    // original bytes back to the loader. We should find a way to remove this
    // additional copy.
    [m_originalData appendBytes:data length:length];

    dispatch_semaphore_t neFilterSourceSemaphore = dispatch_semaphore_create(0);
    [m_neFilterSource addData:[NSData dataWithBytes:(void*)data length:length] withCompletionQueue:m_neFilterSourceQueue completionHandler:^(NEFilterSourceStatus status, NSData *) {
        m_neFilterSourceStatus = status;
        dispatch_semaphore_signal(neFilterSourceSemaphore);
    }];

    // FIXME: We have to block here since DocumentLoader expects to have a
    // blocked/not blocked answer from the filter immediately after calling
    // addData(). We should find a way to make this asynchronous.
    dispatch_semaphore_wait(neFilterSourceSemaphore, DISPATCH_TIME_FOREVER);
    dispatch_release(neFilterSourceSemaphore);
#endif
}
    
void ContentFilter::finishedAddingData()
{
    ASSERT(needsMoreData());

    if (m_platformContentFilter) {
        ASSERT(![m_replacementData.get() length]);
        m_replacementData = [m_platformContentFilter dataComplete];
    }

#if HAVE(NE_FILTER_SOURCE)
    if (!m_neFilterSource)
        return;

    dispatch_semaphore_t neFilterSourceSemaphore = dispatch_semaphore_create(0);
    [m_neFilterSource dataCompleteWithCompletionQueue:m_neFilterSourceQueue completionHandler:^(NEFilterSourceStatus status, NSData *) {
        m_neFilterSourceStatus = status;
        dispatch_semaphore_signal(neFilterSourceSemaphore);
    }];

    // FIXME: We have to block here since DocumentLoader expects to have a
    // blocked/not blocked answer from the filter immediately after calling
    // finishedAddingData(). We should find a way to make this asynchronous.
    dispatch_semaphore_wait(neFilterSourceSemaphore, DISPATCH_TIME_FOREVER);
    dispatch_release(neFilterSourceSemaphore);
#endif

    ASSERT(!needsMoreData());
}

bool ContentFilter::needsMoreData() const
{
    return [m_platformContentFilter filterState] == kWFEStateBuffering
#if HAVE(NE_FILTER_SOURCE)
        || (m_neFilterSource && m_neFilterSourceStatus == NEFilterSourceStatusNeedsMoreData)
#endif
    ;
}

bool ContentFilter::didBlockData() const
{
    return [m_platformContentFilter wasBlocked]
#if HAVE(NE_FILTER_SOURCE)
        || (m_neFilterSource && m_neFilterSourceStatus == NEFilterSourceStatusBlock)
#endif
    ;
}

const char* ContentFilter::getReplacementData(int& length) const
{
    ASSERT(!needsMoreData());

    if (didBlockData()) {
        length = [m_replacementData length];
        return static_cast<const char*>([m_replacementData bytes]);
    }

    NSData *originalData = m_replacementData.get();
#if HAVE(NE_FILTER_SOURCE)
    if (!originalData)
        originalData = m_originalData.get();
#endif

    length = [originalData length];
    return static_cast<const char*>([originalData bytes]);
}

ContentFilterUnblockHandler ContentFilter::unblockHandler() const
{
    return ContentFilterUnblockHandler { m_platformContentFilter.get() };
}

} // namespace WebCore

#endif // ENABLE(CONTENT_FILTERING)
