#include "EventSystem.h"
#include "Log.h"

namespace PTOS {
#ifdef PTOS_LOGGING
	namespace EventTypes {
		PTOS_API std::unordered_map<EventType, std::string> EVENT_TYPE_NAMES{
			{APP_START, "APP_START"},
			{APP_UPDATE, "APP_UPDATE"},
			{APP_END, "APP_END"},
			{WINDOW_OPEN, "WINDOW_OPEN"},
			{WINDOW_CLOSE, "WINDOW_CLOSE"},
			{WINDOW_MOVE, "WINDOW_MOVE"},
			{WINDOW_RESIZE, "WINDOW_RESIZE"},
			{WINDOW_UPDATE, "WINDOW_UPDATE"},
			{WINDOW_KEY_DOWN, "WINDOW_KEY_DOWN"},
			{WINDOW_KEY_UP, "WINDOW_KEY_UP"},
			{WINDOW_MOUSE_DOWN, "WINDOW_MOUSE_DOWN"},
			{WINDOW_MOUSE_UP, "WINDOW_MOUSE_UP"},
			{WINDOW_MOUSE_SCROLL, "WINDOW_MOUSE_SCROLL"},
			{WINDOW_MOUSE_MOVE, "WINDOW_MOUSE_MOVE"}
		};
	}
#endif

	EventLayer::~EventLayer() {
		for (auto it = listeners.begin(); it != listeners.end(); it++) {
			EventListenerNode* node = it->second, *next;
			while (node != nullptr) {
				next = node->next;
				delete node;
				node = next;
			}
		}
		listeners.clear();
	}

	bool EventLayer::addListener(EventType type, const EventListener& listener) {
		auto entry = listeners.find(type);
		if (entry == listeners.end()) {
			EventListenerNode* node = new EventListenerNode;
			node->listener = listener;
			listeners[type] = node;
		}
		else {
			EventListenerNode* node = entry->second;
			//node should never be nullptr, let any errors happen if it is
			if (node->listener.handler == listener.handler) {
				node->listener = listener;
				return false;
			}
			while (node->next != nullptr) {
				node = node->next;
				if (node->listener.handler == listener.handler) {
					node->listener = listener;
					return false;
				}
			}
			node->next = new EventListenerNode;
			node->next->listener = listener;
		}
		return true;
	}

	void EventLayer::addListener(EventType type, EventListenerFunc listener) {
		EventListener listenerData;
		listenerData.handler = listener;
		addListener(type, listenerData);
	}

	bool EventLayer::removeListener(EventType type, EventListenerFunc listener) {
		auto entry = listeners.find(type);
		if (entry == listeners.end())
			return false;
		EventListenerNode* node = entry->second;
		//node should never be nullptr, let any errors happen if it is
		if (node->next == nullptr && node->listener.handler == listener) {
			delete node;
			listeners.erase(entry);
			return true;
		}
		while (node->next != nullptr) {
			if (node->next->listener.handler == listener) {
				EventListenerNode* pop = node->next;
				node->next = pop->next;
				delete pop;
				return true;
			}
		}
		return false;
	}

	bool EventLayer::hasListener(EventType type, EventListenerFunc listener) {
		auto entry = listeners.find(type);
		if (entry == listeners.end())
			return false;
		EventListenerNode* node = entry->second;
		while (node != nullptr) {
			if (node->listener.handler == listener)
				return true;
			node = node->next;
		}
		return false;
	}

	EventResult EventLayer::handle(const EventContext& ctx, bool isBubble, bool isCapture) {
		EventType type = ctx.event.type;
		auto entry = listeners.find(type);
		if (entry == listeners.end())
			return EventResult{};

		EventResult finalResult{};

		EventListenerNode* node = entry->second;
		while (node != nullptr) {
			if ((isBubble && node->listener.bubble) || (isCapture && node->listener.capture)) {
				EventResult res = node->listener.handler(ctx);
				finalResult.cancelBubble |= res.cancelBubble;
				finalResult.cancelCapture |= res.cancelCapture;
				finalResult.cancelLayer |= res.cancelLayer;

				if (finalResult.cancelLayer)
					return finalResult;
			}
			node = node->next;
		}

		return finalResult;
	}

	EventSystem::EventSystem(Application* app) {
		this->app = app;
		layers = layersTail = nullptr;
		eventQueue = eventQueueTail = nullptr;
	}

	EventSystem::~EventSystem() {
		while (layers != nullptr) {
			layersTail = layers->next; //use layers tail as container for next
			delete layers;
			layers = layersTail;
		}
		clearEventQueue();
	}

	void EventSystem::addLayer(EventLayer* layer, double priority) {
		if (layers == nullptr) {
			layers = layersTail = new EventLayerNode{layer, priority};
		}
		else if (priority > layersTail->priority) {
			layersTail = new EventLayerNode{layer, priority, layersTail};
			layersTail->prev->next = layersTail;
		}
		else if (priority < layers->priority) {
			layers = new EventLayerNode{layer, priority, nullptr, layers};
			layers->next->prev = layers;
		}
		else {
			EventLayerNode* node = layers->next;
			while (node != nullptr) {
				if (priority < node->priority) {
					node->prev->next = new EventLayerNode{layer, priority, node->prev, node};
					break;
				}
				node = node->next;
			}
		}
	}
	
	bool EventSystem::removeLayer(EventLayer* layer) {
		if (layers == nullptr)
			return false;
		else if (layer == layers->layer) {
			EventLayerNode* node = layers;
			layers = layers->next;
			if (layers != nullptr)
				layers->prev = nullptr;
			delete node;
			return true;
		}
		else if (layer == layersTail->layer) {
			EventLayerNode* node = layersTail;
			layersTail = layers->prev;
			if (layersTail != nullptr)
				layersTail->next = nullptr;
			delete node;
			return true;
		}
		else {
			EventLayerNode* node = layers->next;
			while (node != nullptr) {
				if (node->layer == layer) {
					node->prev->next = node->next;
					delete node;
					return true;
				}
			}
			return false;
		}
	}

	void EventSystem::addEvent(const EventLayer* layer, const Event& event) {
		PTOS_ASSERT(layer != nullptr, "layer cannot be nullptr");
#ifdef PTOS_LOGGING
		auto entry = EventTypes::EVENT_TYPE_NAMES.find(event.type);
		if (layer != EventLayers::APPLICATION) {
			if (entry == EventTypes::EVENT_TYPE_NAMES.end())
				PTOS_CORE_TRACE("New Event [{0}@{1}]", event.type, (void*)layer);
			else
				PTOS_CORE_TRACE("New Event [{0}@{1}]", entry->second, (void*)layer);
		}
#endif
		if (eventQueueTail == nullptr) {
			eventQueueTail = eventQueue = new EventQueueNode{{event, layer, this}};
		}
		else {
			eventQueueTail->next = new EventQueueNode{{event, layer, this}};
			eventQueueTail = eventQueueTail->next;
		}
	}

	void EventSystem::handle() {
		EventQueueNode* queued = eventQueue, *next;
		//clear the queue so that other events can be built up and not interfere with this call to EventSystem::handle
		eventQueue = eventQueueTail = nullptr;

		while (queued != nullptr) {
			EventLayerNode* layerNode = layers;
			bool nbubble = false, ncapture = false;
			while (layerNode != nullptr) {
				if (layerNode->layer == queued->ctx.layer)
					break;
				layerNode = layerNode->next;
			}
			if (layerNode != nullptr) {
				while (layerNode != nullptr) {
					EventResult result = layerNode->layer->handle(queued->ctx, true, false);
					nbubble |= result.cancelBubble;
					ncapture |= result.cancelCapture;
					if (result.cancelLayer)
						break;
					layerNode = layerNode->next;
				}
				if (!ncapture) {
					if (layerNode == nullptr)
						layerNode = layersTail;
					while (layerNode != nullptr) {
						EventResult result = layerNode->layer->handle(queued->ctx, false, true);
						ncapture |= result.cancelCapture;
						if (ncapture)
							break;
						layerNode = layerNode->prev;
					}
				}
			}
			if (queued->ctx.event.data != nullptr) {
				delete queued->ctx.event.data;
			}
			next = queued->next;
			delete queued;
			queued = next;
		}
	}

	void EventSystem::clearEventQueue() {
		while (eventQueue != nullptr) {
			if (eventQueue->ctx.event.data != nullptr) {
				delete eventQueue->ctx.event.data;
			}
			eventQueueTail = eventQueue->next; //use event queue tail as container for next
			delete eventQueue;
			eventQueue = eventQueueTail;
		}
		eventQueue = eventQueueTail = nullptr;
	}

	namespace EventLayers {
		PTOS_API EventLayer* APPLICATION;
		PTOS_API EventLayer* WINDOW;
		PTOS_API EventLayer* UI;
	}
}