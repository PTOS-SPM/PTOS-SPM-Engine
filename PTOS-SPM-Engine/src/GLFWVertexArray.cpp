#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Buffer.h"
#include "GLFWVertexArray.h"
#include "Log.h"

#define _STR(...) #__VA_ARGS__
#define UNSUPPORT(TYPE, FLAG) { PTOS_CORE_ERR(_STR(GLFW does not support Buffer Element Type TYPE)); PTOS_CORE_ASSERT(false, _STR(Unsupported Buffer Element Type Flag: FLAG)); return GL_NONE; }

#define TYPE_UNSIGNED_FLOAT unsigned float
#define TYPE_UNSIGNED_DOUBLE unsigned double

#define FLAG_UNSIGN unsign

namespace PTOS {

	GLenum convertElementType(const BuffElmType& type) {
		switch (type.name)
		{
		case BufferElementTypeName::BOOL:
			return GL_BOOL;
		case BufferElementTypeName::INT:
			return type.unsign ? GL_UNSIGNED_INT : GL_INT;
		case BufferElementTypeName::FLOAT:
			if (type.unsign)
				UNSUPPORT(TYPE_UNSIGNED_FLOAT, FLAG_FLOAT)
			else return GL_FLOAT;
		case BufferElementTypeName::DOUBLE:
			if (type.unsign)
				UNSUPPORT(TYPE_UNSIGNED_DOUBLE, FLAG_UNSIGN)
			else
				return GL_DOUBLE;
		default:
			PTOS_CORE_ERR("Unknown Buffer Element Type: {0}", (unsigned int)type.name);
			PTOS_CORE_ASSERT(false, "Unknown Buffer Element Type");
			[[fallthrough]];
		case BufferElementTypeName::NONE:
			return GL_NONE;
		}
	}

	void GLFWVertexArray::create() {
		if (id) return;
		glGenVertexArrays(1, &id);
		glBindVertexArray(id);
	}

	void GLFWVertexArray::bind() {
		glBindVertexArray(id);
	}

	void GLFWVertexArray::unbind() {
		glBindVertexArray(0);
	}

	void GLFWVertexArray::addVertexBuffer(VertexBuffer* buffer) {
		PTOS_CORE_ASSERT(buffer->getLayout().getElements().size() > 0, "VertexBuffer is empty");
		glBindVertexArray(id);
		buffer->bind();
		const auto& layout = buffer->getLayout();
		int index = 0;
		for (const auto& elm : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				elm.type.count,
				convertElementType(elm.type),
				elm.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)elm.offset
			);
			index++;
		}
		vertexBuffers.push_back(buffer);
	}

	void GLFWVertexArray::setIndexBuffer(IndexBuffer* buffer) {
		glBindVertexArray(id);
		indexBuffer = buffer;
	}

	void GLFWVertexArray::del() {
		glDeleteVertexArrays(1, &id);
		id = 0;
		vertexBuffers.clear();
		indexBuffer = nullptr;
	}
}
