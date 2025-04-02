#include "WindowRenderer.h"

namespace PTOS {
	WindowRenderer::WindowRenderer(EventSystem* esys, EventLayer* eventLayer) {
		this->esys = esys;
		this->eventLayer = eventLayer;
	}
}