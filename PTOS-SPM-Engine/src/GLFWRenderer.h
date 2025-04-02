#pragma once

#include "Renderer.h"

namespace PTOS {
	class GLFWRenderer : public Renderer {
	public:
		void setClearColor(const rgba& color) override;
		void clear() override;
		void drawIndexed(VertexArray* vertexArray) override;
	};
}