#pragma once

#include "predefines.h"

#include <initializer_list>
#include <string>
#include <vector>

#define _PTOS_BET_DEF_F(name, size, flt)\
	static inline BuffElmType name(uint32_t count, bool unsign) { return BuffElmType(BuffElmTypeName::name, count, size, unsign, flt); }\
	static inline BuffElmType name(uint32_t count) { return name(count, false); }\
	static inline BuffElmType name() { return name(1); }
#define _PTOS_BET_DEF(name, size) _PTOS_BET_DEF_F(name, size, false);

#define _PTOS_BET_DEF_SINGLE(name) BuffElmType::name = BuffElmType::name();

namespace PTOS {
	enum class BuffElmTypeName : uint16_t {
		NONE = 0, BOOL, INT, FLOAT, DOUBLE
	};

	struct BuffElmType {
		inline static BuffElmType NONE() { return BuffElmType(); }
		_PTOS_BET_DEF(BOOL, sizeof(bool))
		_PTOS_BET_DEF(INT, sizeof(int))
		_PTOS_BET_DEF_F(FLOAT, sizeof(float), true)
		_PTOS_BET_DEF_F(DOUBLE, sizeof(double), true)

		BuffElmType() {
			name = BuffElmTypeName::NONE;
			count = 0;
			size = 0;
			unsign = false;
			floating = false;
		}

		BuffElmType(BuffElmTypeName name, uint32_t count, uint32_t size, bool unsign, bool floating);

		BuffElmType(BuffElmTypeName name, uint32_t count, uint32_t size) : BuffElmType(name, count, size, false, false) {}

		BuffElmTypeName name;
		uint32_t count;
		uint32_t size;
		bool unsign;
		bool floating;

		inline uint32_t totalsize() const { return size * count; }
	};

	struct BufferElement {

		BufferElement() {}

		BufferElement(BuffElmType& type, const std::string& name, bool normalized);

		BufferElement(BuffElmType& type, const std::string& name) : BufferElement(type, name, false) {}

		BuffElmType type;
		std::string name;
		size_t offset = 0;
		bool normalized = false;
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::vector<BufferElement>& elements) {
			this->elements = elements;
			calc();
		}

		BufferLayout(const std::initializer_list<BufferElement>& ilist) : BufferLayout(std::vector<BufferElement>(ilist)) {}

		inline const std::vector<BufferElement>& getElements() const { return elements; }
		inline uint32_t getStride() const { return stride; }

		inline std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

		void calc();

	private:
		uint32_t stride = 0; //offset of whole layout (sum of element offsets)
		std::vector<BufferElement> elements;
	};

	class VertexBuffer {
	public:
		virtual void create(float* verticies, size_t size) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual uint32_t getCount() = 0;
		virtual inline const BufferLayout& getLayout() = 0;
		virtual inline void setLayout(const BufferLayout& layout) = 0;
	protected:
		virtual void del() = 0;
	};

	class IndexBuffer {
	public:
		virtual void create(uint32_t* indices, size_t size) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual uint32_t getCount() = 0;
	protected:
		virtual void del() = 0;
	};
}