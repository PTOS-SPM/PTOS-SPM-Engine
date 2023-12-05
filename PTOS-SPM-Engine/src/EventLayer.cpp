#include "EventLayer.h"

namespace PTOS {

	//dispatchEvent function
	void EventLayer::dispatchEvent(Event* event) {
		eventQueue.push_back(event);
	}

	//addEventListener function
	void EventLayer::addEventListener(EventType type, std::function<void(Event*)> listener) {
		eventListeners[type].push_back(listener);
	}

	//handleEvents function
	void EventLayer::handleEvents() {
		for (Event* event : eventQueue) {
			auto eventType = event->type;
			if (eventListeners.find(eventType) != eventListeners.end()) {
				for (auto& listener : eventListeners[eventType]) {
					listener(event); //invokes the listener function
				}
			}
		}
		eventQueue.clear(); //clears processed events
	}

	//getEventQueue function
	const std::vector<Event*>& EventLayer::getEventQueue() const {
		return eventQueue;
	}
}