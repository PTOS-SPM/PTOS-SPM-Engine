#pragma once

#include <vector>

#include "symbols/application.h"
#include "symbols/eventsystem.h"

namespace PTOS {

	struct EventTypeLL {
		EventType type;
		EventTypeLL* next = nullptr;
	};

	class EventSystem {

	public:
		EventSystem(Application* app);
		~EventSystem();

		bool addLayer(EventLayer* layer);
		bool insertLayer(EventLayer* layer, float priority);
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

		Application* app;
		std::vector<EventLayer*> layers;
		EventTypeLL* types = nullptr;
	};
};

