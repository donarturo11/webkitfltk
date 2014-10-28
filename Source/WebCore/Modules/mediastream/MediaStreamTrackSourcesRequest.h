/*
 * Copyright (C) 2013 Google Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY GOOGLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL GOOGLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MediaStreamTrackSourcesRequest_h
#define MediaStreamTrackSourcesRequest_h

#if ENABLE(MEDIA_STREAM)

#include "MediaStreamTrackSourcesRequestClient.h"
#include "SourceInfo.h"
#include "Timer.h"
#include <wtf/RefPtr.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class MediaStreamTrackSourcesCallback;
class ScriptExecutionContext;

class MediaStreamTrackSourcesRequest : public MediaStreamTrackSourcesRequestClient {
public:
    static PassRefPtr<MediaStreamTrackSourcesRequest> create(ScriptExecutionContext*, PassRefPtr<MediaStreamTrackSourcesCallback>);
    virtual ~MediaStreamTrackSourcesRequest() { }

private:
    MediaStreamTrackSourcesRequest(ScriptExecutionContext*, PassRefPtr<MediaStreamTrackSourcesCallback>);

    // MediaStreamTrackSourcesRequestClient
    virtual const String& requestOrigin() const override { return m_origin; }
    virtual void didCompleteRequest(const Vector<RefPtr<TrackSourceInfo>>&) override;

    String m_origin;
    RefPtr<MediaStreamTrackSourcesCallback> m_callback;
    Vector<RefPtr<SourceInfo>> m_sourceInfos;
};

} // namespace WebCore

#endif // MediaStreamTrackSourcesRequest_h

#endif
