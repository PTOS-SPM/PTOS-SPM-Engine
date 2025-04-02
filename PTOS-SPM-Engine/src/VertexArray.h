#pragma once

#include "predefines.h"
#include <vector>


namespace PTOS {

	class VertexArray {
	public:
		virtual void create() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void addVertexBuffer(VertexBuffer* buffer) = 0;
		virtual IndexBuffer* getIndexBuffer() = 0;
		virtual void setIndexBuffer(IndexBuffer* buffer) = 0;
	protected:
		virtual void del() = 0;
	};

}
