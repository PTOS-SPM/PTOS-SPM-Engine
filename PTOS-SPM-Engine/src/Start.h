#pragma once

#include "Application.h"
#include "ApplicationEvent.h"
#include "EventSystem.h"
#include "Input.h"
#include "Log.h"
#include "Window.h"
#include "WindowEvent.h"

#include "Hooks.h"

extern PTOS_HOOK_CREATE_APPLICATION;
extern PTOS_HOOK_START_APPLICATION;
extern PTOS_HOOK_END_APPLICATION;
extern PTOS_HOOK_PRE_UPDATE;
extern PTOS_HOOK_POST_UPDATE;

//make an event system and default layers
PTOS::EventSystem* initEventSystem(PTOS::Application* application) {
	PTOS::EventSystem* esys = new PTOS::EventSystem(application);
	
	PTOS::EventLayer* appLayer = new PTOS::EventLayer((PTOS::EventType*)PTOS::APP_EVENT_TYPES, PTOS::APP_EVENT_COUNT);
	PTOS::EventLayer* winLayer = new PTOS::EventLayer((PTOS::EventType*)PTOS::WINDOW_EVENT_TYPES, PTOS::WINDOW_EVENT_COUNT);
	PTOS::EventLayer* uiLayer = new PTOS::EventLayer();

	//add input event listeners

	PTOS::Input::addEventListeners(winLayer);

	esys->addLayer(appLayer);
	esys->addLayer(winLayer);
	esys->addLayer(uiLayer);

	return esys;
}

int main(int argc, char** argv) {
	//start logging
	PTOS::Log::init();

	PTOS_CORE_TRACE("Creating Application");
	PTOS::Application* app = PTOS::PTOS_HOOKNAME_CREATE_APPLICATION();
	PTOS_CORE_INFO("Created Application");

	PTOS::EventSystem* esys = initEventSystem(app);

	PTOS::ApplicationContextManager appCtxM(PTOS::ApplicationContext{ app, esys });

	PTOS_CORE_TRACE("Starting Application");
	PTOS::PTOS_HOOKNAME_START_APPLICATION(appCtxM);
	PTOS_CORE_INFO("Started Application");

	while (app->doRun()) {
		PTOS::PTOS_HOOKNAME_PRE_UPDATE(appCtxM);

		//handle events
		esys->handle(); //NOTE: while windows only update at their given framerate, the Event System is still being handled every iteration

		//handle windows
		app->windows.handle();

		PTOS::PTOS_HOOKNAME_POST_UPDATE(appCtxM);
	}

	PTOS_CORE_TRACE("Ending Application");
	PTOS::PTOS_HOOKNAME_END_APPLICATION(app);
	PTOS_CORE_INFO("Ended Application");

	return 0;
}
