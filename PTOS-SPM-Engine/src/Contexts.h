#pragma once

#include "Application.h"
#include "Core.h"
#include "EventSystem.h"

namespace PTOS {
	struct ApplicationContext {
		Application* app;
		EventSystem* eventSystem;
	};
	struct EventContext {
		EventSystem* system = nullptr;
		EventLayer* layer = nullptr;
		EventListenerFunc listener = nullptr;
		Event* event = nullptr;
		Application* app;
	};
}