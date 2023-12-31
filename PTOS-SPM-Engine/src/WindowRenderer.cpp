#include <iostream>

#include "EventLayer.h"
#include "WindowRenderer.h"

namespace PTOS {

	WindowRenderer::WindowRenderer(EventLayer* eventLayer) {
		this->eventLayer = eventLayer;
		vsync = VSYNC_DEFAULT;
	}

}

std::ostream& operator<< (std::ostream& out, PTOS::WindowRenderer& renderer) {
	return out << "<" << renderer.getRendererName() << "\"" << renderer.getTitle()
		<< "\" (" << renderer.getWidth() << "x" << renderer.getHeight() << ") at "
		<< &renderer << ">";
}