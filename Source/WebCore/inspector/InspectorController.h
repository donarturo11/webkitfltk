/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef InspectorController_h
#define InspectorController_h

#include "InspectorInstrumentationCookie.h"
#include "InspectorOverlay.h"
#include <inspector/InspectorAgentRegistry.h>
#include <inspector/InspectorEnvironment.h>
#include <wtf/Forward.h>
#include <wtf/HashMap.h>
#include <wtf/Noncopyable.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace Inspector {
class BackendDispatcher;
class FrontendChannel;
class InspectorAgent;
class InspectorObject;

namespace Protocol {
namespace OverlayTypes {
class NodeHighlightData;
}
}
}

namespace WebCore {

class DOMWrapperWorld;
class Frame;
class GraphicsContext;
class InspectorClient;
class InspectorDOMAgent;
class InspectorDOMDebuggerAgent;
class InspectorFrontendClient;
class InspectorInstrumentation;
class InspectorPageAgent;
class InspectorResourceAgent;
class InspectorTimelineAgent;
class InstrumentingAgents;
class Node;
class Page;
class PageDebuggerAgent;
class WebInjectedScriptManager;

class InspectorController final : public Inspector::InspectorEnvironment {
    WTF_MAKE_NONCOPYABLE(InspectorController);
    WTF_MAKE_FAST_ALLOCATED;
public:
    InspectorController(Page&, InspectorClient*);
    virtual ~InspectorController();

    void inspectedPageDestroyed();

    bool enabled() const;
    Page& inspectedPage() const;

    WEBCORE_EXPORT void show();
    WEBCORE_EXPORT void close();

    WEBCORE_EXPORT void setInspectorFrontendClient(InspectorFrontendClient*);
    bool hasInspectorFrontendClient() const;
    void didClearWindowObjectInWorld(Frame&, DOMWrapperWorld&);

    WEBCORE_EXPORT void dispatchMessageFromFrontend(const String& message);

    bool hasFrontend() const { return !!m_frontendChannel; }
    bool hasLocalFrontend() const;
    bool hasRemoteFrontend() const;

    WEBCORE_EXPORT void connectFrontend(Inspector::FrontendChannel*, bool isAutomaticInspection);
    WEBCORE_EXPORT void disconnectFrontend(Inspector::DisconnectReason);
    void setProcessId(long);

#if ENABLE(REMOTE_INSPECTOR)
    void setHasRemoteFrontend(bool hasRemote) { m_hasRemoteFrontend = hasRemote; }
#endif

    void inspect(Node*);
    WEBCORE_EXPORT void drawHighlight(GraphicsContext&) const;
    WEBCORE_EXPORT void getHighlight(Highlight&, InspectorOverlay::CoordinateSystem) const;
    void hideHighlight();
    Node* highlightedNode() const;

    void setIndicating(bool);

    WEBCORE_EXPORT RefPtr<Inspector::Protocol::OverlayTypes::NodeHighlightData> buildObjectForHighlightedNode() const;

    bool isUnderTest() const { return m_isUnderTest; }
    void setIsUnderTest(bool isUnderTest) { m_isUnderTest = isUnderTest; }
    WEBCORE_EXPORT void evaluateForTestInFrontend(const String& script);

    WEBCORE_EXPORT bool profilerEnabled() const;
    WEBCORE_EXPORT void setProfilerEnabled(bool);

    void resume();

    InspectorClient* inspectorClient() const { return m_inspectorClient; }
    InspectorPageAgent* pageAgent() const { return m_pageAgent; }

    virtual bool developerExtrasEnabled() const override;
    virtual bool canAccessInspectedScriptState(JSC::ExecState*) const override;
    virtual Inspector::InspectorFunctionCallHandler functionCallHandler() const override;
    virtual Inspector::InspectorEvaluateHandler evaluateHandler() const override;
    virtual void willCallInjectedScriptFunction(JSC::ExecState*, const String& scriptName, int scriptLine) override;
    virtual void didCallInjectedScriptFunction(JSC::ExecState*) override;
    virtual void frontendInitialized() override;
    virtual Ref<WTF::Stopwatch> executionStopwatch() override;

private:
    friend class InspectorInstrumentation;

    RefPtr<InstrumentingAgents> m_instrumentingAgents;
    std::unique_ptr<WebInjectedScriptManager> m_injectedScriptManager;
    std::unique_ptr<InspectorOverlay> m_overlay;

    Inspector::InspectorAgent* m_inspectorAgent;
    InspectorDOMAgent* m_domAgent;
    InspectorResourceAgent* m_resourceAgent;
    InspectorPageAgent* m_pageAgent;
    PageDebuggerAgent* m_debuggerAgent;
    InspectorDOMDebuggerAgent* m_domDebuggerAgent;
    InspectorTimelineAgent* m_timelineAgent;

    RefPtr<Inspector::BackendDispatcher> m_backendDispatcher;
    Inspector::FrontendChannel* m_frontendChannel;
    Ref<WTF::Stopwatch> m_executionStopwatch;
    Page& m_page;
    InspectorClient* m_inspectorClient;
    InspectorFrontendClient* m_inspectorFrontendClient;
    Inspector::AgentRegistry m_agents;
    Vector<InspectorInstrumentationCookie, 2> m_injectedScriptInstrumentationCookies;
    bool m_isUnderTest;
    bool m_isAutomaticInspection;

#if ENABLE(REMOTE_INSPECTOR)
    bool m_hasRemoteFrontend;
#endif
};

}

#endif // !defined(InspectorController_h)
