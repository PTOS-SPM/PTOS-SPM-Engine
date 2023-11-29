#include <PTOS.h>

PTOS::Application* PTOS::createApplication(void) {
	return new Application();
}