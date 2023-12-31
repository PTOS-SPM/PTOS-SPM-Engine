#pragma once

#include "VertexArray.h"

namespace PTOS {
	class GLFWVertexArray : public VertexArray {
	public:
		PTOS_OVERRIDE_VERTEX_ARRAY_METHODS_PUBLIC(GLFWVertexArray)
	protected:
		PTOS_OVERRIDE_VERTEX_ARRAY_METHODS_PROTECTED()
	private:
		std::vector<VertexBuffer*> vertexBuffers;
		IndexBuffer* indexBuffer;
		unsigned int id = 0;
	};
}