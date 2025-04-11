#pragma once

#include "predefines.h"
#include <string>

namespace PTOS {
	class Texture {
	public:
		//Gets the texture's width
		virtual uint32_t getWidth() = 0;
		//Gets the texture's height
		virtual uint32_t getHeight() = 0;

		//Binds the texture to the rendering context
		virtual void bind(uint32_t slot=0) = 0;
		//Unbinds the texture from the rendering context
		virtual void unbind() = 0;
	};

	class Texture2D : public Texture {
	public:
		//Creates a new texture from the file at the given path
		static Texture2D* create(const std::string& path);
	};
}
