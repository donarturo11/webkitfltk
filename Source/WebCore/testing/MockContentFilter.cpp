/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
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

#include "config.h"
#include "MockContentFilter.h"

#if ENABLE(CONTENT_FILTERING)

#include "ContentFilter.h"
#include "ContentFilterUnblockHandler.h"
#include "Logging.h"
#include "ResourceRequest.h"
#include "ResourceResponse.h"
#include "SharedBuffer.h"
#include <mutex>
#include <wtf/text/CString.h>
#include <wtf/text/StringBuilder.h>

namespace WebCore {

using Decision = MockContentFilterSettings::Decision;
using DecisionPoint = MockContentFilterSettings::DecisionPoint;

void MockContentFilter::ensureInstalled()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []{
        ContentFilter::addType<MockContentFilter>();
    });
}

static inline MockContentFilterSettings& settings()
{
    return MockContentFilterSettings::singleton();
}

bool MockContentFilter::enabled()
{
    bool enabled = settings().enabled();
    LOG(ContentFiltering, "MockContentFilter is %s.\n", enabled ? "enabled" : "not enabled");
    return enabled;
}

std::unique_ptr<MockContentFilter> MockContentFilter::create()
{
    return std::make_unique<MockContentFilter>();
}

void MockContentFilter::willSendRequest(ResourceRequest&, const ResourceResponse& redirectResponse)
{
    if (redirectResponse.isNull())
        maybeDetermineStatus(DecisionPoint::AfterWillSendRequest);
    else
        maybeDetermineStatus(DecisionPoint::AfterRedirect);
}

void MockContentFilter::responseReceived(const ResourceResponse&)
{
    maybeDetermineStatus(DecisionPoint::AfterResponse);
}

void MockContentFilter::addData(const char*, int)
{
    maybeDetermineStatus(DecisionPoint::AfterAddData);
}

void MockContentFilter::finishedAddingData()
{
    maybeDetermineStatus(DecisionPoint::AfterFinishedAddingData);
}

bool MockContentFilter::needsMoreData() const
{
    return m_status == Status::NeedsMoreData;
}

bool MockContentFilter::didBlockData() const
{
    return m_status == Status::Blocked;
}

Ref<SharedBuffer> MockContentFilter::replacementData() const
{
    ASSERT(didBlockData());
    return adoptRef(*SharedBuffer::create(m_replacementData.data(), m_replacementData.size()).leakRef());
}

ContentFilterUnblockHandler MockContentFilter::unblockHandler() const
{
    ASSERT(didBlockData());
    using DecisionHandlerFunction = ContentFilterUnblockHandler::DecisionHandlerFunction;

    return ContentFilterUnblockHandler {
        MockContentFilterSettings::unblockURLHost(), [](DecisionHandlerFunction decisionHandler) {
            bool shouldAllow { settings().unblockRequestDecision() == Decision::Allow };
            if (shouldAllow)
                settings().setDecision(Decision::Allow);
            LOG(ContentFiltering, "MockContentFilter %s the unblock request.\n", shouldAllow ? "allowed" : "did not allow");
            decisionHandler(shouldAllow);
        }
    };
}

String MockContentFilter::unblockRequestDeniedScript() const
{
    return ASCIILiteral("unblockRequestDenied()");
}

void MockContentFilter::maybeDetermineStatus(DecisionPoint decisionPoint)
{
    if (m_status != Status::NeedsMoreData || decisionPoint != settings().decisionPoint())
        return;

    LOG(ContentFiltering, "MockContentFilter stopped buffering with status %u at decision point %u.\n", m_status, decisionPoint);

    m_status = settings().decision() == Decision::Allow ? Status::Allowed : Status::Blocked;
    if (m_status != Status::Blocked)
        return;

    m_replacementData.clear();
    const CString utf8BlockedString = settings().blockedString().utf8();
    m_replacementData.append(utf8BlockedString.data(), utf8BlockedString.length());
}

} // namespace WebCore

#endif // ENABLE(CONTENT_FILTERING)
