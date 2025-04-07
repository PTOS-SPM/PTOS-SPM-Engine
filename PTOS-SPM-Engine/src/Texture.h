#pragma once

#include "predefines.h"
#include <string>

namespace PTOS {
	class Texture {
	public:
		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;

		virtual void bind(uint32_t slot=0) = 0;
	};

	class Texture2D : public Texture {
	public:
		
		static Texture2D* create(const std::string& path);
	};
}
