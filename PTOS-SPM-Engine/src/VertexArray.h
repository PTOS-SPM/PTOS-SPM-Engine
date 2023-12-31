#pragma once

#include "symbols/window.h"
#include <vector>

#define PTOS_OVERRIDE_VERTEX_ARRAY_METHODS_PUBLIC(name) \
		~name() { unbind(); del(); } \
		void create() override; \
		void bind() override; \
		void unbind() override; \
		void addVertexBuffer(VertexBuffer* buffer) override; \
		void setIndexBuffer(IndexBuffer* buffer) override; \

#define PTOS_OVERRIDE_VERTEX_ARRAY_METHODS_PROTECTED() \
		void del() override; \

namespace PTOS {

	class VertexArray {
	public:
		virtual void create() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void addVertexBuffer(VertexBuffer* buffer) = 0;
		virtual void setIndexBuffer(IndexBuffer* buffer) = 0;
	protected:
		virtual void del() = 0;
	};

}
