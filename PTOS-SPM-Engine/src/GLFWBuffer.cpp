#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "GLFWBuffer.h"

namespace PTOS {
	//Vertex Buffer

	GLFWVertexBuffer::GLFWVertexBuffer(unsigned int id) { this->id = id; }
	GLFWVertexBuffer::GLFWVertexBuffer(unsigned int id, unsigned int count) : GLFWVertexBuffer(id) { this->count = count; }

	void GLFWVertexBuffer::create(float* verticies, size_t size) {
		if (id) return;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW); //DEBUG static draw
		count = size > 0 ? (unsigned int)(size / sizeof(verticies[0])) : 0;
	}

	void GLFWVertexBuffer::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	
	void GLFWVertexBuffer::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	unsigned int GLFWVertexBuffer::getCount() { return count; }

	inline const BufferLayout& GLFWVertexBuffer::getLayout() { return layout; }

	inline void GLFWVertexBuffer::setLayout(const BufferLayout& layout) { this->layout = layout; }

	void GLFWVertexBuffer::del() {
		glDeleteBuffers(1, &id);
		count = 0;
		id = 0;
	}

	//Index Buffer

	GLFWIndexBuffer::GLFWIndexBuffer(unsigned int id) { this->id = id; }
	GLFWIndexBuffer::GLFWIndexBuffer(unsigned int id, unsigned int count) : GLFWIndexBuffer(id) { this->count = count; }

	void GLFWIndexBuffer::create(unsigned int* indices, size_t size) {
		if (id) return;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); //DEBUG static draw
		count = size > 0 ? (unsigned int)(size / sizeof(indices[0])) : 0;
	}

	void GLFWIndexBuffer::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void GLFWIndexBuffer::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int GLFWIndexBuffer::getCount() { return count; }

	void GLFWIndexBuffer::del() {
		glDeleteBuffers(1, &id);
		count = 0;
		id = 0;
	}
}
