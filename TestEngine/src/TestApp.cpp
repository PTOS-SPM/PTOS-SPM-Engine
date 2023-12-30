#include <PTOS.h>

PTOS::Window* mainWindow = nullptr;

PTOS::WindowRenderer* makeRenderer(PTOS::EventLayer* layer) {
	return (PTOS::WindowRenderer*)(new PTOS::GLFWRenderer(layer));
}

void onWindowClose(PTOS::EventContext& ctx) {
	PTOS::WindowEvent* event = (PTOS::WindowEvent*)ctx.event;
	event->getRenderer()->shutdown(); //perma-close window

	//if window closed was the main window, then stop the app

	if (event->getRenderer() == mainWindow->getRenderer())
		ctx.app->stop();
	event->stopPropagate();
	event->stopHandle();
}

void onWindowUpdate(PTOS::EventContext& ctx) {
	PTOS::WindowEvent* event = (PTOS::WindowEvent*)ctx.event;
	PTOS::Input input(event->getRenderer());

	if (event->getRenderer() != mainWindow->getRenderer())
		return;

	for (auto& pair : input.getAnyAll()) {
		PTOS_DEBUG("{0}: {1}", (int)pair.first, pair.second.count);
	}
}

void onStart(PTOS::ApplicationContextManager& ctx) {
	if (mainWindow) return;

	//setup windows

	mainWindow = ctx.newWindow(800, 450, std::string("Test Application"), nullptr, makeRenderer);
	mainWindow->open();

	PTOS::Window* subwindow = ctx.newWindow(800, 450, std::string("Sub Window"), nullptr, makeRenderer);
	subwindow->open();

	//create Game Layer

	PTOS::EventLayer* gameLayer = ctx.newLayer();

	//add event listeners

	gameLayer->addListener(PTOS::WINDOW_CLOSE, onWindowClose);
	gameLayer->addListener(PTOS::WINDOW_UPDATE, onWindowUpdate);
}

PTOS_HOOK_CREATE_APPLICATION_DEFAULT

PTOS_HOOK_START_APPLICATION {
	onStart(ctx);
}

PTOS_HOOK_END_APPLICATION {
	delete application;
}

PTOS_HOOK_PRE_UPDATE_DEFAULT
PTOS_HOOK_POST_UPDATE_DEFAULT
