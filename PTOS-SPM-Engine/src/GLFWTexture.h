#pragma once

#include "predefines.h"
#include "Texture.h"

namespace PTOS {
	class GLFWTexture2D : public Texture2D {
	public:
		GLFWTexture2D(const std::string& path);
		~GLFWTexture2D();

		inline uint32_t getWidth() override { return width; }
		inline uint32_t getHeight() override { return height; }

		void bind(uint32_t slot) override;
		void unbind() override;

	private:
		std::string path;
		uint32_t width;
		uint32_t height;
		uint32_t textureId;
	};
}