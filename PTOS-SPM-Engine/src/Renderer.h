#pragma once

#include "predefines.h"
#include "ptosmath.h"

#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"

namespace PTOS {
	
	// takes 4 hex vales (rgba) and stores them as percents (x / 0xff) in a vec4
	inline rgba rgbaHexToP(float r, float g, float b, float a = 0xff) { return rgba(r / 0xff, g / 0xff, b / 0xff, a / 0xff); }

	struct SceneInfo {
		~SceneInfo();

		Camera2D* camera = nullptr;
		Shader* shader = nullptr;
		VertexArray* vertexArray = nullptr;
	};

	class Renderer {
	public:
		void submit(SceneInfo* scene);

		virtual void setClearColor(const rgba& color) = 0;
		virtual void clear() = 0;
		virtual void drawIndexed(VertexArray* vertexArray) = 0;
	};
}