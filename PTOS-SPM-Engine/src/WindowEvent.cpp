#include "Event.h"
#include "WindowEvent.h"

namespace PTOS {
	WindowEvent::WindowEvent(WindowEventType type, WindowRenderer* renderer) : Event((EventType)type) {
		this->renderer = renderer;
	}
	WindowEvent::WindowEvent(WindowEventType type, WindowRenderer* renderer, int code) : WindowEvent(type, renderer) {
		this->code = code;
	}
	WindowEvent::WindowEvent(WindowEventType type, WindowRenderer* renderer, int x, int y) : WindowEvent(type, renderer) {
		this->x = x;
		this->y = y;
	}
	WindowEvent::WindowEvent(WindowEventType type, WindowRenderer* renderer, double x, double y) : WindowEvent(type, renderer) {
		this->x = x;
		this->y = y;
	}
}