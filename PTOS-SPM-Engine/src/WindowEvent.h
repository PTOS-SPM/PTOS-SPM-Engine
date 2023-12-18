#pragma once

#include "symbols/eventsystem.h"
#include "symbols/window.h"

#include "Event.h"

namespace PTOS {

	const EventType WINDOW_EVENT_BEGIN = 100;

	//Code 100 -> 199
	enum WindowEventType : EventType {
		WINDOW_OPEN = WINDOW_EVENT_BEGIN,
		WINDOW_CLOSE,
		WINDOW_MOVE,
		WINDOW_RESIZE,
		WINDOW_UPDATE,
		WINDOW_KEY_DOWN,
		WINDOW_KEY_UP,
		WINDOW_MOUSE_DOWN,
		WINDOW_MOUSE_UP,
		WINDOW_MOUSE_SCROLL,
		WINDOW_MOUSE_MOVE
	};

	const WindowEventType WINDOW_EVENT_TYPES[] = { WINDOW_OPEN, WINDOW_CLOSE, WINDOW_MOVE, WINDOW_RESIZE };
	const size_t WINDOW_EVENT_COUNT = sizeof(WINDOW_EVENT_TYPES) / sizeof(WINDOW_EVENT_TYPES[0]);

	class WindowEvent: public Event
	{
	public:
		WindowEvent(WindowEventType type, WindowRenderer* renderer);
		WindowEvent(WindowEventType type, WindowRenderer* renderer, int code);
		WindowEvent(WindowEventType type, WindowRenderer* renderer, int x, int y);
		WindowEvent(WindowEventType type, WindowRenderer* renderer, double x, double y);

		inline WindowRenderer* getRenderer() { return renderer; }
		inline int getWidth() const { return (int)x; }
		inline int getHeight() const { return (int)y; }
		inline int getMoveX() const { return (int)x; }
		inline int getMoveY() const { return (int)y; }
		inline double getMouseX() const { return x; }
		inline double getMouseY() const { return y; }
		inline double getScrollX() const { return x; }
		inline double getScrollY() const { return y; }
		inline int getKeyCode() const { return code; }
		inline int getMouseButton() const { return code; }

	private:
		WindowRenderer* renderer;
		double x = 0;
		double y = 0;
		int code = -1;
	};
}

