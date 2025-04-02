#pragma once

#include "predefines.h"

#ifdef PTOS_LOGGING
#include <string>
#endif
#include <unordered_map>

//Use or lack of use of this term doesn't control anything, but it helps to signify to any readers that the event system will free this data
#define PTOS_EVENTDATA new

namespace PTOS {

	struct Event {
		EventType type;
		void* data = nullptr;
	};

	struct EventContext {
		const Event event;
		const EventLayer* layer;
		const EventSystem* esys;

	};

	struct EventResult {
		bool cancelLayer = false;
		bool cancelBubble = false;
		bool cancelCapture = false;
	};

	struct EventQueueNode {
		EventContext ctx;
		EventQueueNode* next = nullptr;
	};

	struct EventListener {
		EventListenerFunc handler = nullptr;
		bool bubble = true;
		bool capture = false;
	};

	struct EventListenerNode {
		EventListener listener;
		EventListenerNode* next = nullptr;
	};


	namespace EventLayers {
		const double PRIORITY_APPLICATION = 0;
		const double PRIORITY_WINDOW = 100;
		const double PRIORITY_UI = 200;
		const double PRIORITY_USER_DEFAULT = 500;

		extern EventLayer* APPLICATION;
		extern EventLayer* WINDOW;
		extern EventLayer* UI;
	}

	class EventLayer {
	public:
		EventLayer() {};
		~EventLayer();

		bool addListener(EventType type, const EventListener& listener);
		void addListener(EventType type, EventListenerFunc listener);
		bool removeListener(EventType type, EventListenerFunc listener);
		bool hasListener(EventType type, EventListenerFunc listener);
		EventResult handle(const EventContext& ctx, bool isBubble, bool isCapture);

	private:
		std::unordered_map<EventType, EventListenerNode*> listeners;
	};

	struct EventLayerNode {
		EventLayer* layer;
		double priority;
		EventLayerNode* prev = nullptr;
		EventLayerNode* next = nullptr;
	};

	class EventSystem {
	public:
		EventSystem(Application* app);
		~EventSystem();

		void addLayer(EventLayer* layer, double priority=EventLayers::PRIORITY_USER_DEFAULT);
		bool removeLayer(EventLayer* layer);
		void addEvent(const EventLayer* layer, const Event& event);
		void handle();
		void clearEventQueue();

	protected:
		Application* app;
	private:
		EventLayerNode* layers;
		EventLayerNode* layersTail;
		EventQueueNode* eventQueue;
		EventQueueNode* eventQueueTail;
	};
	

	namespace EventTypes {
		enum BuiltinEventTypes : EventType {
			APP_START,
			APP_UPDATE,
			APP_END,

			WINDOW_OPEN,
			WINDOW_CLOSE,
			WINDOW_MOVE,
			WINDOW_RESIZE,
			WINDOW_UPDATE,
			WINDOW_KEY_DOWN,
			WINDOW_KEY_UP,
			WINDOW_MOUSE_DOWN,
			WINDOW_MOUSE_UP,
			WINDOW_MOUSE_SCROLL,
			WINDOW_MOUSE_MOVE,


			BUILTIN_END = WINDOW_MOUSE_MOVE + 1
		};

#ifdef PTOS_LOGGING
		extern std::unordered_map<EventType, std::string> EVENT_TYPE_NAMES;
#endif
	}
};