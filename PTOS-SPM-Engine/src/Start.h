#pragma once

#include "Application.h"
#include "Core.h"

#include <iostream>

extern PTOS::Application* PTOS::createApplication(void);

int main(int argc, char** argv) {
	PTOS::Application* app = PTOS::createApplication();
	
	std::cout << "Start Application\n";

	//TODO run application
	while (true); //DEBUG

	delete app;
	return 0;
}
