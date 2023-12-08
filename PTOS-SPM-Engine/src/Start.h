#pragma once

#include "Application.h"
#include "Core.h"
#include "EventSystem.h"
#include "Window.h"
#include "WindowEvent.h"

#include "Contexts.h"

#include <iostream>

extern PTOS::Application* PTOS::createApplication();
extern void PTOS::startApplication(PTOS::ApplicationContext& ctx);
extern void PTOS::endApplication(PTOS::Application* application);

//make an event system and default layers
PTOS::EventSystem* initEventSystem(PTOS::Application* application) {
	PTOS::EventSystem* esys = new PTOS::EventSystem(application);

	//TODO add layer codes
	
	PTOS::EventLayer* appLayer = new PTOS::EventLayer();
	PTOS::EventLayer* winLayer = new PTOS::EventLayer((PTOS::EventType*)PTOS::WINDOW_EVENT_TYPES, PTOS::WINDOW_EVENT_COUNT);
	PTOS::EventLayer* uiLayer = new PTOS::EventLayer();

	esys->addLayer(appLayer);
	esys->addLayer(winLayer);
	esys->addLayer(uiLayer);

	return esys;
}

int main(int argc, char** argv) {
	//start logging
	PTOS::Log::init();

	PTOS_CORE_TRACE("Creating Application");
	PTOS::Application* app = PTOS::createApplication();
	PTOS_CORE_INFO("Created Application");

	PTOS::EventSystem* esys = initEventSystem(app);

	PTOS::ApplicationContext appCtx{app, esys};

	PTOS_CORE_TRACE("Starting Application");
	PTOS::startApplication(appCtx);
	PTOS_CORE_INFO("Started Application");

	while (app->doRun()) {
		//handle windows
		app->windows.handle();
		//handle events
		esys->handle();
	}

	PTOS_CORE_TRACE("Ending Application");
	PTOS::endApplication(app);
	PTOS_CORE_INFO("Ended Application");

	return 0;
}
