#pragma once

#include "Log.h"
#include "Application.h"
#include "Input.h"
#include "EventSystem.h"


PTOS::EventSystem* EVENTS = nullptr;

extern void PTOSInit(PTOS::Application* app);

void initEventSystem(PTOS::Application* app) {
	EVENTS = new PTOS::EventSystem(app);

	PTOS::EventLayers::APPLICATION = new PTOS::EventLayer();
	PTOS::EventLayers::WINDOW = new PTOS::EventLayer();
	PTOS::EventLayers::UI = new PTOS::EventLayer();

	PTOS_CORE_INFO("Layer APPLICATION\t{0}", (void*)PTOS::EventLayers::APPLICATION);
	PTOS_CORE_INFO("Layer WINDOW\t{0}", (void*)PTOS::EventLayers::WINDOW);
	PTOS_CORE_INFO("Layer UI\t{0}", (void*)PTOS::EventLayers::UI);

	PTOS::Input::addEventListeners(PTOS::EventLayers::WINDOW);

	EVENTS->addLayer(PTOS::EventLayers::APPLICATION, PTOS::EventLayers::PRIORITY_APPLICATION);
	EVENTS->addLayer(PTOS::EventLayers::WINDOW, PTOS::EventLayers::PRIORITY_WINDOW);
	EVENTS->addLayer(PTOS::EventLayers::UI, PTOS::EventLayers::PRIORITY_UI);

#ifdef PTOS_LOGGING
	PTOS::EventLayers::APPLICATION->addListener(PTOS::EventTypes::APP_START, [](const PTOS::EventContext& ctx) { PTOS_CORE_INFO("Started Application"); return PTOS::EventResult{}; });
	PTOS::EventLayers::APPLICATION->addListener(PTOS::EventTypes::APP_END, [](const PTOS::EventContext& ctx) { PTOS_CORE_INFO("Ended Application"); return PTOS::EventResult{}; });
#endif

}

int main(int argc, char** argv) {
	//start logging
	PTOS::Log::init();

	PTOS_CORE_TRACE("Creating Application");
	PTOS::Application* app = new PTOS::Application();
	PTOS_CORE_INFO("Created Application");

	initEventSystem(app);

	PTOSInit(app);

	EVENTS->addEvent(PTOS::EventLayers::APPLICATION, { PTOS::EventTypes::APP_START, PTOS_EVENTDATA PTOS::ApplicationEvent{ app }});

	PTOS_CORE_TRACE("Starting Application");
	EVENTS->handle();

	while (app->doRun()) {
		EVENTS->addEvent(PTOS::EventLayers::APPLICATION, { PTOS::EventTypes::APP_UPDATE, PTOS_EVENTDATA PTOS::ApplicationEvent{ app } });

		//handle events
		EVENTS->handle(); //NOTE: while windows only update at their given framerate, the Event System is still being handled every iteration

		//handle windows
		app->handle();

		//handle events again
		EVENTS->handle();
	}

	EVENTS->handle();

	PTOS_CORE_TRACE("Ending Application");
	EVENTS->addEvent(PTOS::EventLayers::APPLICATION, { PTOS::EventTypes::APP_END, PTOS_EVENTDATA PTOS::ApplicationEvent{app} });
	EVENTS->handle();

	delete app;

	return 0;
}