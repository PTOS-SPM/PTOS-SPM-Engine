#pragma once

#include "Application.h"
#include "Core.h"
#include "EventSystem.h"

#include <iostream>

extern PTOS::Application* PTOS::createApplication(void);

int main(int argc, char** argv) {
	PTOS::Log::init();
	PTOS_CORE_TRACE("Creating Application");
	PTOS::Application* app = PTOS::createApplication();
	PTOS_CORE_TRACE("Created Application");

	//TODO run application
	while (true); //DEBUG

	delete app;
	return 0;
}
