#pragma once

#include "VertexArray.h"

namespace PTOS {
	class GLFWVertexArray : public VertexArray {
	public:
		~GLFWVertexArray() { unbind(); del(); }
		void create() override;
		void bind() override;
		void unbind() override;
		void addVertexBuffer(VertexBuffer* buffer) override;
		IndexBuffer* getIndexBuffer() override;
		void setIndexBuffer(IndexBuffer* buffer) override;
	protected:
		void del() override;
	private:
		std::vector<VertexBuffer*> vertexBuffers;
		IndexBuffer* indexBuffer = nullptr;
		unsigned int id = 0;
	};
}