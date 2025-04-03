#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Buffer.h"
#include "GLFWRenderer.h"
#include "VertexArray.h"

namespace PTOS {
	//NOTE: temporary implementaitions

	void GLFWRenderer::setClearColor(const rgba& color) {
		glClearColor(color[0], color[1], color[2], color[3]);
	}

	void GLFWRenderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLFWRenderer::drawIndexed(VertexArray* vertexArray) {
		vertexArray->bind();
		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}
