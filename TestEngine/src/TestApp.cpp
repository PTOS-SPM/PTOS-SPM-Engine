#include <PTOS.h>

class TestApplication : public PTOS::Application {
public:
	TestApplication() {

	}

	~TestApplication() {

	}
};

PTOS::Application* PTOS::createApplication(void) {
	return new TestApplication();
}
