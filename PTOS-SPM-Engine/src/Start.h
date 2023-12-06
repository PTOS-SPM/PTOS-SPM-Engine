#pragma once

#include "Application.h"
#include "Core.h"

#include <iostream>

extern PTOS::Application* PTOS::startApplication(ApplicationContext& ctx);
extern void PTOS::endApplication(PTOS::Application* application);

int main(int argc, char** argv) {
	PTOS::Log::init();

	PTOS::ApplicationContext appCtx;

	PTOS_CORE_TRACE("Starting Application");
	PTOS::Application* app = PTOS::startApplication(appCtx);
	PTOS_CORE_INFO("Started Application");

	while (app->doRun()) {
		for (int i = 0; i < app->windows.size(); i++) {
			app->windows.get(i)->update();
		}

		//TODO handle dispatched events
	}

	PTOS_CORE_TRACE("Ending Application");
	PTOS::endApplication(app);
	PTOS_CORE_INFO("Ended Application");
	return 0;
}
