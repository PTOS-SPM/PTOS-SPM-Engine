#include <PTOS.h>
#include <sstream>

class TestApplication : public PTOS::Application { };

PTOS::Application* PTOS::startApplication(PTOS::ApplicationContext& ctx) {
	TestApplication* app = new TestApplication();

	Window* window = PTOS_NEW_WINDOW(800, 450, "Test Application", nullptr, new GLFWRenderer());
	window->open();

	app->windows.add(window);

	return app;
}

void PTOS::endApplication(Application* application) {
	delete application;
}
