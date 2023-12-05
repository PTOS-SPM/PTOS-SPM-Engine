#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

namespace PTOS {
	enum class EventType {
		mouse_click,
		key_press
	};

	struct Event {
		EventType type;
	};
	class EventLayer {
	private:
		std::vector<Event*> eventQueue;
		std::unordered_map<EventType, std::vector<std::function<void(Event*)>>> eventListeners;

	public:
		void dispatchEvent(Event* event) {
			eventQueue.push_back(event);
		}

		void addEventListener(EventType type, std::function<void(Event*)> listener) {
			eventListeners[type].push_back(listener);
		}

		void handleEvents() {
			for (Event* event : eventQueue) {
				auto eventType = event->type;
				if (eventListeners.find(eventType) != eventListeners.end()) {
					for (auto& listener : eventListeners[eventType]) {
						listener(event); //invoke the listener function
					}
				}
			}
			eventQueue.clear(); //clears processed events
		}

		const std::vector<Event*>& getEventQueue() const {
			return eventQueue;
		}
	};

	int main() {
		EventLayer eventLayer;

		auto mouseClickListener = [](Event* event) {
			std::cout << "mouse click event handled\n";
		};

		auto keyPressListener = [](Event* event) {
			std::cout << "key press event handled\n";
		};

		eventLayer.addEventListener(EventType::mouse_click, mouseClickListener);
		eventLayer.addEventListener(EventType::key_press, keyPressListener);

		Event mouseClickEvent{ EventType::mouse_click };
		Event keyPressEvent{ EventType::key_press };

		eventLayer.dispatchEvent(&mouseClickEvent);
		eventLayer.dispatchEvent(&keyPressEvent);

		eventLayer.handleEvents();
		
		return 0;
	}
};
