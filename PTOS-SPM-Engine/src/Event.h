#pragma once

#include "symbols/eventsystem.h"

namespace PTOS {

	class Event {
	public:
		Event(EventType type, bool propagate, bool handle);
		Event(EventType type) : Event(type, true, true) {}

		inline bool shouldPropagate() const { return propagate; }
		inline bool shouldHandle() const { return handle; }
		inline EventType getType() const { return type; }
	
		void stopPropagate();
		void stopHandle();

	private:
		Event() : Event(0) {}
		bool propagate;
		bool handle;
		EventType type;

	};
}

