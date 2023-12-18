#include "Application.h"
#include "EventLayer.h"
#include "Log.h"

#include <iostream>

namespace PTOS {

	EventLayer::EventLayer(const EventType* types, size_t typeCount) {
		this->types = types;
		this->typeCount = typeCount;
		queue = std::vector<Event*>();
		listeners = std::unordered_map<EventType, std::vector<EventListenerFunc>>();
	}

	EventLayer::~EventLayer() {
		for (auto event = queueBegin(); event != queueEnd(); event++)
			delete *event;
		queue.clear();
		listeners.clear();
		delete types;
	}

	void EventLayer::dispatch(Event* event) {
		queue.push_back(event);
	}

	void EventLayer::addListener(EventType type, EventListenerFunc listener) {
		if (listeners.find(type) == listeners.end())
			listeners[type] = std::vector<EventListenerFunc>();
		//can only add the same listener once
		else if (hasListener(type, listener)) return;
		listeners[type].push_back(listener);
	}

	bool EventLayer::hasListener(EventType type, EventListenerFunc listener) {
		auto index = listeners.find(type);
		if (index == listenersEnd()) return false;

		auto search = index->second;
		for (auto lst = search.begin(); lst != search.end(); lst++)
			if (*lst == listener)
				return true;
		return false;
	}

	bool EventLayer::hasListener(EventListenerFunc listener) {
		for (auto pair = listenersBegin(); pair != listenersEnd(); pair++)
			if (hasListener(pair->first, listener)) return true;
		return false;
	}

	bool EventLayer::removeListener(EventType type, EventListenerFunc listener) {
		auto index = listeners.find(type);
		if (index == listenersEnd()) return true;
		
		auto search = index->second;
		for (auto lst = search.begin(); lst != search.end(); lst++) {
			if (*lst == listener) {
				search.erase(lst);
				return true;
			}
		}
		return false;
	}

	bool EventLayer::removeListener(EventListenerFunc listener) {
		bool removed = false;
		for (auto pair = listenersBegin(); pair != listenersEnd(); pair++)
			if (removeListener(pair->first, listener) && !removed) removed = true;
		return removed;
	}

}

std::ostream& operator<< (std::ostream& os, PTOS::EventLayer& layer) {
	return os << "<EventLayer (" << layer.getTypeCount() << ") (" << (layer.queueEnd() - layer.queueBegin()) + 1
		<< ") at " << &layer << ">";
}
