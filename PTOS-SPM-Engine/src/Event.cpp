#include "Event.h"
#include "Log.h"

#include <iostream>

namespace PTOS {
	Event::Event(EventType type, bool propagate, bool handle) {
		this->type = type;
		this->propagate = propagate;
		this->handle = handle;
	}

	void Event::stopPropagate() {
		propagate = false;
	}

	void Event::stopHandle() {
		handle = false;
	}
}

std::ostream& operator<< (std::ostream& os, PTOS::Event& event) {
	return os << "<Event (" << event.getType() << ") handle=" << event.shouldHandle() <<
		", propagate=" << event.shouldPropagate() << " at " << &event << ">";
}
