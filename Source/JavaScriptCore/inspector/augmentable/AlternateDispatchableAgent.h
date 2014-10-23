/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AlternateDispatchableAgent_h
#define AlternateDispatchableAgent_h

#if ENABLE(INSPECTOR_ALTERNATE_DISPATCHERS)

#include "InspectorAlternateBackendDispatchers.h"
#include "InspectorBackendDispatchers.h"
#include <JavaScriptCore/InspectorAgentBase.h>
#include <wtf/Forward.h>

namespace Inspector {

template<typename BackendDispatcher, typename AlternateDispatcher>
class AlternateDispatchableAgent final : public InspectorAgentBase {
    WTF_MAKE_FAST_ALLOCATED;
public:
    AlternateDispatchableAgent(const String& domainName, std::unique_ptr<AlternateDispatcher> alternateDispatcher)
        : InspectorAgentBase(domainName)
        , m_alternateDispatcher(WTF::move(alternateDispatcher))
    {
    }

    virtual void didCreateFrontendAndBackend(InspectorFrontendChannel*, InspectorBackendDispatcher* backendDispatcher) override
    {
        m_backendDispatcher = BackendDispatcher::create(backendDispatcher, nullptr);
        m_backendDispatcher->setAlternateDispatcher(m_alternateDispatcher.get());
        m_alternateDispatcher->setBackendDispatcher(backendDispatcher);
    }

    virtual void willDestroyFrontendAndBackend(InspectorDisconnectReason) override
    {
        m_backendDispatcher = nullptr;
        m_alternateDispatcher->setBackendDispatcher(nullptr);
    }

private:
    std::unique_ptr<AlternateDispatcher> m_alternateDispatcher;
    RefPtr<BackendDispatcher> m_backendDispatcher;
};

} // namespace Inspector

#endif // ENABLE(INSPECTOR_ALTERNATE_DISPATCHERS)

#endif // AlternateDispatchableAgent_h
