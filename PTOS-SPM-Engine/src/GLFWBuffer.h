#pragma once

#include "Buffer.h"

namespace PTOS {

	class GLFWVertexBuffer : public VertexBuffer {
	public:
		GLFWVertexBuffer() {}
		GLFWVertexBuffer(uint32_t id);
		GLFWVertexBuffer(uint32_t id, uint32_t count);
		~GLFWVertexBuffer() { unbind(); del(); }

		void create(float* verticies, size_t size) override;
		void bind() override;
		void unbind() override;
		uint32_t getCount() override;
		inline const BufferLayout& getLayout() override;
		inline void setLayout(const BufferLayout& layout) override;

	protected:
		void del() override;
	private:
		BufferLayout layout;
		uint32_t count = 0;
		uint32_t id = 0;
	};

	class GLFWIndexBuffer : public IndexBuffer {
	public:
		GLFWIndexBuffer() {}
		GLFWIndexBuffer(uint32_t id);
		GLFWIndexBuffer(uint32_t id, uint32_t count);
		~GLFWIndexBuffer() { unbind(); del(); } \

		void create(uint32_t* indices, size_t size) override;
		void bind() override;
		void unbind() override;
		uint32_t getCount() override;

	protected:
		void del() override;
	private:
		uint32_t count = 0;
		uint32_t id = 0;
	};
}