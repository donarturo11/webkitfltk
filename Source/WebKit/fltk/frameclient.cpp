/*
WebkitFLTK
Copyright (C) 2014 Lauri Kasanen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, version 3 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"
#include "frameclient.h"
#include "webviewpriv.h"

#include <wtf/text/CString.h>
#include <DocumentLoader.h>
#include <FrameNetworkingContext.h>
#include <ErrorsFLTK.h>
#include <MainFrame.h>
#include <MIMETypeRegistry.h>
#include <NotImplemented.h>
#include <ResourceError.h>
#include <ResourceRequest.h>

using namespace WebCore;
using namespace WTF;

extern const char * (*uafunc)(const char *);

FlFrameLoaderClient::FlFrameLoaderClient(webview *inview, Frame *inframe) {
	view = inview;
	frame = inframe ? inframe : &inview->priv->page->mainFrame();
}

bool FlFrameLoaderClient::hasHTMLView() const {
	return true;
}

void FlFrameLoaderClient::frameLoaderDestroyed() {
	delete this;
}

bool FlFrameLoaderClient::hasWebView() const {
	return true;
}

void FlFrameLoaderClient::makeRepresentation(DocumentLoader*) {
	notImplemented();
}

void FlFrameLoaderClient::forceLayoutForNonHTML() {
	notImplemented();
}

void FlFrameLoaderClient::setCopiesOnScroll() {
	notImplemented();
}

void FlFrameLoaderClient::detachedFromParent2() {
	notImplemented();
}

void FlFrameLoaderClient::detachedFromParent3() {
	notImplemented();
}

void FlFrameLoaderClient::assignIdentifierToInitialRequest(unsigned long identifier, DocumentLoader*, const ResourceRequest&) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchWillSendRequest(DocumentLoader*, unsigned long identifier, ResourceRequest&, const ResourceResponse& redirectResponse) {
	notImplemented();
}

bool FlFrameLoaderClient::shouldUseCredentialStorage(DocumentLoader*, unsigned long identifier) {
	return false;
}

void FlFrameLoaderClient::dispatchDidReceiveAuthenticationChallenge(DocumentLoader*, unsigned long identifier, const AuthenticationChallenge&) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidCancelAuthenticationChallenge(DocumentLoader*, unsigned long identifier, const AuthenticationChallenge&) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidReceiveResponse(DocumentLoader*, unsigned long identifier, const ResourceResponse&) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidReceiveContentLength(DocumentLoader*, unsigned long identifier, int dataLength) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidFinishLoading(DocumentLoader*, unsigned long identifier) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidFailLoading(DocumentLoader*, unsigned long identifier, const ResourceError&) {
	notImplemented();
}

bool FlFrameLoaderClient::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const ResourceRequest&, const ResourceResponse&, int length) {
	notImplemented();
	return false;
}

void FlFrameLoaderClient::dispatchDidHandleOnloadEvents() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidReceiveServerRedirectForProvisionalLoad() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidCancelClientRedirect() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchWillPerformClientRedirect(const URL&, double interval, double fireDate) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidChangeLocationWithinPage() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidPushStateWithinPage() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidReplaceStateWithinPage() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidPopStateWithinPage() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchWillClose() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidReceiveIcon() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidStartProvisionalLoad() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidReceiveTitle(const StringWithDirection&) {
}

void FlFrameLoaderClient::dispatchDidChangeIcons(IconType) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidCommitLoad() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidFailProvisionalLoad(const ResourceError &error) {
	dispatchDidFailLoad(error);
}

void FlFrameLoaderClient::dispatchDidFailLoad(const ResourceError&) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidFinishDocumentLoad() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidFinishLoad() {
	view->redraw();
}

Frame* FlFrameLoaderClient::dispatchCreatePage(const NavigationAction&) {
	return 0;
}

void FlFrameLoaderClient::dispatchShow() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDecidePolicyForResponse(const ResourceResponse &resp,
		const ResourceRequest &req, FramePolicyFunction policyfunc) {
	if (!policyfunc)
		return;
	if (req.isNull()) {
		policyfunc(PolicyIgnore);
		return;
	}

	if (canShowMIMEType(resp.mimeType()))
		policyfunc(PolicyUse);
	else
		policyfunc(PolicyDownload);
}

void FlFrameLoaderClient::dispatchDecidePolicyForNewWindowAction(const NavigationAction&, const ResourceRequest&, PassRefPtr<FormState>,
		const String& frameName, FramePolicyFunction policyfunc) {
	policyfunc(PolicyUse);
}

void FlFrameLoaderClient::dispatchDecidePolicyForNavigationAction(const NavigationAction&, const ResourceRequest&,
		PassRefPtr<FormState>, FramePolicyFunction policyfunc) {
	policyfunc(PolicyUse);
}

void FlFrameLoaderClient::cancelPolicyCheck() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchUnableToImplementPolicy(const ResourceError&) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchWillSendSubmitEvent(PassRefPtr<FormState>) {
	notImplemented();
}

void FlFrameLoaderClient::dispatchWillSubmitForm(PassRefPtr<FormState>,
			FramePolicyFunction policyfunc) {
	if (!policyfunc)
		return;

	policyfunc(PolicyUse);
}

void FlFrameLoaderClient::revertToProvisionalState(DocumentLoader*) {
	notImplemented();
}

void FlFrameLoaderClient::setMainDocumentError(DocumentLoader*, const ResourceError&) {
	notImplemented();
}

void FlFrameLoaderClient::setMainFrameDocumentReady(bool) {
	notImplemented();
}

void FlFrameLoaderClient::startDownload(const ResourceRequest&, const String& suggestedName) {
	notImplemented();
}

void FlFrameLoaderClient::willChangeTitle(DocumentLoader*) {
}

void FlFrameLoaderClient::didChangeTitle(DocumentLoader *documentLoader) {
	setTitle(documentLoader->title(), documentLoader->url());
}

void FlFrameLoaderClient::committedLoad(DocumentLoader *loader, const char *data, int len) {
	loader->commitData(data, len);
}

void FlFrameLoaderClient::finishedLoading(DocumentLoader*) {
	notImplemented();
}

void FlFrameLoaderClient::updateGlobalHistory() {
	notImplemented();
}

void FlFrameLoaderClient::updateGlobalHistoryRedirectLinks() {
	notImplemented();
}

bool FlFrameLoaderClient::shouldGoToHistoryItem(HistoryItem *item) const {
	return item != 0;
}

// FlFrameLoaderClient::This frame has displayed inactive content (such as an image) from an
// insecure source.  Inactive content cannot spread to other frames.
void FlFrameLoaderClient::didDisplayInsecureContent() {
	notImplemented();
}

// FlFrameLoaderClient::The indicated security origin has run active content (such as a
// script) from an insecure source.  Note that the insecure content can
// spread to other frames in the same origin.
void FlFrameLoaderClient::didRunInsecureContent(SecurityOrigin*, const URL&) {
	notImplemented();
}

void FlFrameLoaderClient::didDetectXSS(const URL&, bool didBlockEntirePage) {
	notImplemented();
}

ResourceError FlFrameLoaderClient::cancelledError(const ResourceRequest &req) {
	return WebCore::cancelledError(req);
}

ResourceError FlFrameLoaderClient::blockedError(const ResourceRequest &req) {
	return WebCore::blockedError(req);
}

ResourceError FlFrameLoaderClient::cannotShowURLError(const ResourceRequest &req) {
	return WebCore::cannotShowURLError(req);
}

ResourceError FlFrameLoaderClient::interruptedForPolicyChangeError(const ResourceRequest &req) {
	return WebCore::interruptedForPolicyChangeError(req);
}

ResourceError FlFrameLoaderClient::cannotShowMIMETypeError(const ResourceResponse &resp) {
	return WebCore::cannotShowMIMETypeError(resp);
}

ResourceError FlFrameLoaderClient::fileDoesNotExistError(const ResourceResponse &resp) {
	return WebCore::fileDoesNotExistError(resp);
}

ResourceError FlFrameLoaderClient::pluginWillHandleLoadError(const ResourceResponse &resp) {
	return WebCore::pluginWillHandleLoadError(resp);
}

bool FlFrameLoaderClient::shouldFallBack(const ResourceError &error) {
	return !(error.isCancellation());
}

bool FlFrameLoaderClient::canHandleRequest(const ResourceRequest&) const {
	notImplemented();
	return true;
}

bool FlFrameLoaderClient::canShowMIMEType(const String& MIMEType) const {
	return MIMETypeRegistry::canShowMIMEType(MIMEType);
}

bool FlFrameLoaderClient::canShowMIMETypeAsHTML(const String& MIMEType) const {
	notImplemented();
	return false;
}

bool FlFrameLoaderClient::representationExistsForURLScheme(const String& URLScheme) const {
	notImplemented();
	return false;
}

String FlFrameLoaderClient::generatedMIMETypeForURLScheme(const String& URLScheme) const {
	notImplemented();
	return String();
}

void FlFrameLoaderClient::frameLoadCompleted() {
	notImplemented();
}

void FlFrameLoaderClient::saveViewStateToItem(HistoryItem*) {
	notImplemented();
}

void FlFrameLoaderClient::restoreViewState() {
	notImplemented();
}

void FlFrameLoaderClient::provisionalLoadStarted() {
	notImplemented();
}

void FlFrameLoaderClient::didFinishLoad() {
	notImplemented();
}

void FlFrameLoaderClient::prepareForDataSourceReplacement() {
	notImplemented();
}

PassRefPtr<DocumentLoader> FlFrameLoaderClient::createDocumentLoader(const ResourceRequest& req,
		const SubstituteData &data) {
	RefPtr<DocumentLoader> loader = DocumentLoader::create(req, data);
	return loader;
}

void FlFrameLoaderClient::setTitle(const StringWithDirection &title, const URL &url) {
	printf("Title set to '%s' URL '%s'\n",
		title.string().utf8().data(), url.string().utf8().data());
	notImplemented();
}

String FlFrameLoaderClient::userAgent(const URL &url) {
	if (uafunc)
		return uafunc(decodeURLEscapeSequences(url.string()).utf8().data());
	return String("Mozilla/5.0 (Windows NT 5.1; rv:31.0) Gecko/20100101 Firefox/31.0");
}

void FlFrameLoaderClient::savePlatformDataToCachedFrame(CachedFrame*) {
	notImplemented();
}

void FlFrameLoaderClient::transitionToCommittedFromCachedFrame(CachedFrame*) {
	notImplemented();
}

void FlFrameLoaderClient::transitionToCommittedForNewPage() {
	IntSize size(view->w(), view->h());
	frame->createView(size, Color::white, false);
}

void FlFrameLoaderClient::didSaveToPageCache() {
	notImplemented();
}

void FlFrameLoaderClient::didRestoreFromPageCache() {
	notImplemented();
}

void FlFrameLoaderClient::dispatchDidBecomeFrameset(bool) {
	notImplemented();
}

bool FlFrameLoaderClient::canCachePage() const {
	return true;
}

void FlFrameLoaderClient::setFrame(Frame *inframe) {
	frame = inframe;
}

Frame *FlFrameLoaderClient::getFrame() const {
	return frame;
}

void FlFrameLoaderClient::convertMainResourceLoadToDownload(DocumentLoader*, const ResourceRequest&, const ResourceResponse&) {
	notImplemented();
}

PassRefPtr<Frame> FlFrameLoaderClient::createFrame(const URL& url,
		const String& name, HTMLFrameOwnerElement* ownerElement,
		const String& referrer, bool allowsScrolling,
		int marginWidth, int marginHeight) {

	Frame *parent = frame;
	FlFrameLoaderClient *newl = new FlFrameLoaderClient(view);
	RefPtr<Frame> kid = Frame::create(view->priv->page, ownerElement, newl).get();
	newl->setFrame(kid.get());

	kid->tree().setName(name);
	parent->tree().appendChild(kid);
	kid->init();

	// Bad JS may nuke it instantly
	if (!kid->page())
		return NULL;

	parent->loader().loadURLIntoChildFrame(url, referrer, kid.get());

	// Bad JS again
	if (!kid->tree().parent())
		return NULL;

	return kid.release();
}

PassRefPtr<Widget> FlFrameLoaderClient::createPlugin(const IntSize&, HTMLPlugInElement*, const URL&, const Vector<String>&, const Vector<String>&, const String&, bool loadManually) {
	return 0;
}

void FlFrameLoaderClient::recreatePlugin(Widget*) {
}

void FlFrameLoaderClient::redirectDataToPlugin(Widget* pluginWidget) {
}

PassRefPtr<Widget> FlFrameLoaderClient::createJavaAppletWidget(const IntSize&, HTMLAppletElement*, const URL& baseURL, const Vector<String>& paramNames, const Vector<String>& paramValues) {
	return NULL;
}

ObjectContentType FlFrameLoaderClient::objectContentType(const URL &url,
		const String& mimeType, bool preferPlugInsForImages) {
	return FrameLoader::defaultObjectContentType(url, mimeType, preferPlugInsForImages);
}

String FlFrameLoaderClient::overrideMediaType() const {
	notImplemented();
	return String();
}

void FlFrameLoaderClient::dispatchDidClearWindowObjectInWorld(DOMWrapperWorld&) {
	notImplemented();
}

void FlFrameLoaderClient::registerForIconNotification(bool listen) {
	notImplemented();
}

class netctx: public FrameNetworkingContext {
public:
	netctx(Frame *f): FrameNetworkingContext(f) {}
};

PassRefPtr<FrameNetworkingContext> FlFrameLoaderClient::createNetworkingContext() {
	return adoptRef(new netctx(frame));
}
