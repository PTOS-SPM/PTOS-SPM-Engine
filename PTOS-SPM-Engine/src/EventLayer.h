#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "symbols/application.h"
#include "symbols/eventsystem.h"

namespace PTOS {

	class EventLayer {
	public:
		EventLayer(const EventType* types, size_t typeCount);
		EventLayer() : EventLayer(nullptr, 0) {}
		~EventLayer();

		void dispatch(Event* event);
		void addListener(EventType type, EventListenerFunc listener);
		bool hasListener(EventType type, EventListenerFunc listener);
		bool hasListener(EventListenerFunc listener);
		bool removeListener(EventType type, EventListenerFunc listener);
		bool removeListener(EventListenerFunc listener);

		inline const EventType* getTypes() const { return types; }
		inline size_t getTypeCount() const { return typeCount; }
		inline void clearQueue() { queue.clear(); }
		inline std::vector<Event*>::const_iterator queueBegin() const { return queue.begin(); }
		inline std::vector<Event*>::const_iterator queueEnd() const { return queue.end(); }

		//example of unholy c++ type, even using 2 typedefs

		inline std::unordered_map<EventType, std::vector<EventListenerFunc>>::const_iterator listenersBegin() const { return listeners.begin(); }
		inline std::unordered_map<EventType, std::vector<EventListenerFunc>>::const_iterator listenersEnd() const { return listeners.end(); }
		inline std::vector<EventListenerFunc>::iterator getListenerBegin(EventType type) { return listeners[type].begin(); }
		inline std::vector<EventListenerFunc>::iterator getListenerEnd(EventType type) { return listeners[type].end(); }
		inline EventListenerFunc getListener(EventType type, size_t index) { return listeners[type].at(index); }

	private:
		const EventType* types;
		size_t typeCount;
		std::vector<Event*> queue;
		std::unordered_map<EventType, std::vector<EventListenerFunc>> listeners;
	};

	struct EventContext {
		EventLayer* layer = nullptr;
		EventListenerFunc listener = nullptr;
		Event* event = nullptr;
		Application* app = nullptr;
	};

};
