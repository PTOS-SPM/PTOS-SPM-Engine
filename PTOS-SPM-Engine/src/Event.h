#pragma once

namespace PTOS {
	enum class EventType {
		mousemove,
		mousedown,
		mouseup,
		mousescroll
		//add more later on, just defaults for now
	};

	class Event {
	public:
		Event(EventType type, bool propagate = true, bool send = true);

		inline bool shouldPropagate() const { return propagateToNextLayer; }
		inline bool shouldSend() const { return handle; }
		inline EventType getType() const { return eventType; }
	
	private:
		Event() {}
		bool propagateToNextLayer;
		bool handle;
		EventType eventType;

	};

	class MouseInputEvent : public Event {
	public:
		MouseInputEvent(int x, int y, int buttonCode = -1, float scrollDirection = 0);
		
		inline int getMouseX() const { return x; }
		inline int getMouseY() const { return y; }
		inline int ButtonCode() const { return button; }
		inline int getScrollDirection() const { return scrollDirection; }

	private:
		int x;
		int y;
		int button; // mouse button pressed
		float scrollDirection; //scroll wheel direction info
	};
}

