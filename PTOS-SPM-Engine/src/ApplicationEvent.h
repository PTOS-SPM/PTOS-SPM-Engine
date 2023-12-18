#pragma once

#include "symbols/application.h"
#include "symbols/eventsystem.h"
#include "Event.h"

namespace PTOS {

	const EventType APP_EVENT_BEGIN = 0;

	//Code 0 -> 99
	enum ApplicationEventType : EventType {
		APP_UPDATE = APP_EVENT_BEGIN
	};

	const ApplicationEventType APP_EVENT_TYPES[] = { APP_UPDATE };
	const size_t APP_EVENT_COUNT = sizeof(APP_EVENT_TYPES) / sizeof(APP_EVENT_TYPES[0]);

	class ApplicationEvent : public Event {
	public:
		ApplicationEvent(ApplicationEventType type);
	};
}

