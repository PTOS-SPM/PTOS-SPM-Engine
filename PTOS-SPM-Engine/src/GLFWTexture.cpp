#include "GLFWTexture.h"
#include "Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include "glad/glad.h"


namespace PTOS {
	GLFWTexture2D::GLFWTexture2D(const std::string& path) {
		int w, h, comp;

		stbi_set_flip_vertically_on_load(1);

		uint8_t* data = stbi_load(path.c_str(), &w, &h, &comp, 0);
		PTOS_CORE_ASSERT(data != nullptr, "Failed to load texture");

		width = w;
		height = h;

		GLenum format;
		switch (comp) {
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default: {
			PTOS_CORE_ASSERT(false, "Cannot assign format to component count");
			break;
		}
		}

		//cite: https://stackoverflow.com/a/56820908

		glGenTextures(1, &textureId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		//glTextureStorage2D(textureId, 1, GL_RGB8, width, height);

		glTexParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexSubImage2D(textureId, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLFWTexture2D::~GLFWTexture2D() {
		glDeleteTextures(1, &textureId);
	}

	void GLFWTexture2D::bind(uint32_t slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void GLFWTexture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}