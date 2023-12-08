#include <PTOS.h>
#include <sstream>

class TestApplication : public PTOS::Application {
public:
	inline PTOS::Window* getMainWindow() { return mainWindow; }

	void stop() { run = false; }

	void onStart(PTOS::ApplicationContext& ctx) {
		if (started) return;
		started = true;
		
		//setup main window
		PTOS::EventLayer* winLayer = ctx.eventSystem->getLayer(1);
		mainWindow = PTOS_NEW_WINDOW(800, 450, "Test Application", nullptr, new PTOS::GLFWRenderer(winLayer));
		mainWindow->open();

		//add event listeners
		winLayer->addListener(PTOS::WINDOW_CLOSE, [](PTOS::EventContext& ctx) {
			auto event = (PTOS::WindowEvent*)ctx.event;
			event->getRenderer()->shutdown(); //perma-close window

			//if window closed was the main window, then stop the app
			TestApplication* app = (TestApplication*)ctx.app;
			if (event->getRenderer() == app->getMainWindow()->getRenderer())
				app->stop();
			event->stopPropagate();
			event->stopHandle();
		});
		winLayer->addListener(PTOS::WINDOW_MOUSE_MOVE, [](PTOS::EventContext& ctx) {
			auto event = (PTOS::WindowEvent*)ctx.event;
			PTOS_DEBUG("Mouse: ({0}, {1})", event->getScrollX(), event->getScrollY());
		});

		windows.add(mainWindow);
	}

private:
	PTOS::Window* mainWindow;
	bool started = false;
};

PTOS::Application* PTOS::createApplication() {
	return new TestApplication();
}

void PTOS::startApplication(PTOS::ApplicationContext& ctx) {
	TestApplication* app = (TestApplication*)ctx.app;
	app->onStart(ctx);
}

void PTOS::endApplication(Application* application) {
	delete application;
}
