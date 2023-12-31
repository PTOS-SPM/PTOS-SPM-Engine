#include "Buffer.h"

namespace PTOS {
	BuffElmType::BuffElmType(BufferElementTypeName name, unsigned int count, size_t size, bool unsign, bool floating) {
		this->name = name;
		this->count = count;
		this->size = size;
		this->unsign = unsign;
		this->floating = floating;
	}

	BufferElement::BufferElement(BuffElmType& type, const std::string& name, bool normalized) {
		this->type = type;
		this->name = name;
		this->normalized = normalized;
	}

	void BufferLayout::calc() {
		unsigned int offset = 0;
		stride = 0;
		for (BufferElement& elm : elements) {
			//update element offset, lets the element know its position in the layout
			offset += stride;
			elm.offset = offset;
			stride += elm.type.totalsize();
		}
	}
}