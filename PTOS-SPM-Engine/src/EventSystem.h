#pragma once

#include <vector>

#include "EventLayer.h"

namespace PTOS {

	static struct EventTypeLL {
		EventType type;
		EventTypeLL* next = nullptr;
	};

	class PTOS_API EventSystem {

	public:
		EventSystem();
		~EventSystem();

		bool addLayer(EventLayer* layer);
		bool removeLayer(EventLayer* layer);
		bool removeLayer(size_t index);
		std::vector<EventLayer*>::const_iterator findLayer(EventLayer* layer);
		bool hasType(EventType type);

		void handle();

		inline bool hasLayer(EventLayer* layer) { return findLayer(layer) != layersEnd(); }
		inline EventLayer* getLayer(size_t index) const { return layers.at(index); }
		inline std::vector<EventLayer*>::const_iterator layersBegin() const { return layers.begin(); }
		inline std::vector<EventLayer*>::const_iterator layersEnd() const { return layers.end(); }


	private:
		//helper methods

		bool addType(EventType type);
		void removeType(EventType type);
		void handleEvent(Event* event, EventLayer* layer, std::vector<Event*>& pg);

		std::vector<EventLayer*> layers;
		EventTypeLL* types = nullptr;
	};

	struct PTOS_API EventContext {
		EventSystem* system = nullptr;
		EventLayer* layer = nullptr;
		EventListenerFunc listener = nullptr;
		Event* event = nullptr;
	};
};

