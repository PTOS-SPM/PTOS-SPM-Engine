#pragma once

#include "Buffer.h"

namespace PTOS {

	class GLFWVertexBuffer : public VertexBuffer {
	public:
		GLFWVertexBuffer() {}
		GLFWVertexBuffer(unsigned int id);
		GLFWVertexBuffer(unsigned int id, unsigned int count);
		PTOS_OVERRIDE_VERTEX_BUFFER_METHODS_PUBLIC(GLFWVertexBuffer)
	protected:
		PTOS_OVERRIDE_VERTEX_BUFFER_METHODS_PROTECTED()
	private:
		BufferLayout layout;
		unsigned int count = 0;
		unsigned int id = 0;
	};

	class GLFWIndexBuffer : public IndexBuffer {
	public:
		GLFWIndexBuffer() {}
		GLFWIndexBuffer(unsigned int id);
		GLFWIndexBuffer(unsigned int id, unsigned int count);
		PTOS_OVERRIDE_INDEX_BUFFER_METHODS_PUBLIC(GLFWIndexBuffer)
	protected:
		PTOS_OVERRIDE_INDEX_BUFFER_METHODS_PROTECTED()
	private:
		unsigned int count = 0;
		unsigned int id = 0;
	};
}
