#include <PTOS.h>
#include <sstream>

void onWindowClose(PTOS::EventContext& ctx);
void onWindowUpdate(PTOS::EventContext& ctx);

class TestApplication : public PTOS::Application {
public:
	inline PTOS::Window* getMainWindow() { return mainWindow; }

	void stop() { run = false; }

	void onStart(PTOS::ApplicationContextManager& ctx) {
		if (mainWindow) return;
		
		//setup windows

		mainWindow = ctx.newWindow(800, 450, std::string("Test Application"), nullptr, [](PTOS::EventLayer* layer) { return (PTOS::WindowRenderer*)(new PTOS::GLFWRenderer(layer)); });
		mainWindow->open();

		auto subwindow = ctx.newWindow(800, 450, std::string("Sub Window"), nullptr, [](PTOS::EventLayer* layer) { return (PTOS::WindowRenderer*)(new PTOS::GLFWRenderer(layer)); });
		subwindow->open();

		//create Game Layer

		PTOS::EventLayer* gameLayer = ctx.newLayer();

		//add event listeners

		gameLayer->addListener(PTOS::WINDOW_CLOSE, onWindowClose);
		gameLayer->addListener(PTOS::WINDOW_UPDATE, onWindowUpdate);
	}

private:
	PTOS::Window* mainWindow = nullptr;
};

void onWindowClose(PTOS::EventContext& ctx) {
	PTOS::WindowEvent* event = (PTOS::WindowEvent*)ctx.event;
	event->getRenderer()->shutdown(); //perma-close window

	//if window closed was the main window, then stop the app
	TestApplication* app = (TestApplication*)ctx.app;
	if (event->getRenderer() == app->getMainWindow()->getRenderer())
		app->stop();
	event->stopPropagate();
	event->stopHandle();
}

void onWindowUpdate(PTOS::EventContext& ctx) {
	PTOS::WindowEvent* event = (PTOS::WindowEvent*)ctx.event;
	PTOS::Input input(event->getRenderer());

	TestApplication* app = (TestApplication*)ctx.app;
	if (event->getRenderer() != app->getMainWindow()->getRenderer())
		return;

	for (auto& pair : input.getAnyAll()) {
		PTOS_DEBUG("{0}: {1}", (int)pair.first, pair.second.count);
	}
}

PTOS_HOOK_CREATE_APPLICATION {
	return new TestApplication();
}

PTOS_HOOK_START_APPLICATION {
	TestApplication* app = (TestApplication*)ctx.getApplication();
	app->onStart(ctx);
}

PTOS_HOOK_END_APPLICATION {
	delete application;
}

PTOS_HOOK_PRE_UPDATE_DEFAULT
PTOS_HOOK_POST_UPDATE_DEFAULT