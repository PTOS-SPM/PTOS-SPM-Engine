#include "Event.h"

namespace PTOS {
	Event::Event(EventType type, bool propagate, bool send)
		: eventType(type), propagateToNextLayer(propagate), handle(send) {}

	bool Event::shouldPropagate() const {
		return propagateToNextLayer;
	}

	bool Event::shouldSend() const {
		return handle;
	}

	EventType Event::getType() const {
		return eventType;
	}

	MouseInputEvent::MouseInputEvent(int x, int y, int buttonCode, float scrollDirection)
		: Event(EventType::mousemove), x(x), y(y), button(buttonCode), scrollDirection(scrollDirection) {}
	
	int MouseInputEvent::getMouseX() const {
		return x;
	}

	int MouseInputEvent::getMouseY() const {
		return y;
	}

	int MouseInputEvent::ButtonCode() const {
		return button;
	}

	int MouseInputEvent::getScrollDirection() const {
		return scrollDirection;
	}
}