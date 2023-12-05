#pragma once

#include <vector>

namespace PTOS {
	class EventLayer;

	class EventSystem {
	private:
		std::vector<EventLayer*> eventLayers;

	public:
		EventSystem() {}

		~EventSystem() {
			for (EventLayer* layer : eventLayers) {
				delete layer;
			}
			eventLayers.clear();
		}

		void addEventLayer(EventLayer* layer) {
			eventLayers.push_back(layer);
		}
	};
};

