#include "Log.h"
#include "Shader.h"

#ifdef PTOS_RENDER_DYNAMIC
#include "Renderer.h"
#endif

#if defined(PTOS_RENDER_GL) || defined(PTOS_RENDER_DYNAMIC)
#include "glad/glad.h"
#include "GLFWShader.h"
#endif


#define _PTOS_CREATE_SHADER_FILE_GL		std::string* src = nullptr; \
										int* types = nullptr; \
										size_t count = GLFWShader::readFromFile(filename, &src, &types); \
										PTOS_CORE_ASSERT(src != nullptr && types != nullptr && count != 0, "Failed to read shaders from file"); \
										Shader* shader = GLFWShader::compile(src, types, count); \
										delete[] src; \
										delete[] types; \
										return shader; \

#define _PTOS_CREATE_SHADER_GL	std::string srcs[] = { vertexShaderSrc, pixelShaderSrc }; \
								int types[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER }; \
								return GLFWShader::compile(srcs, types, sizeof(srcs) / sizeof(srcs[0])); \


namespace PTOS {

	Shader* Shader::create(const std::string& filename) {
#if defined(PTOS_RENDER_DYNAMIC)
		switch (CURRENT_RENDERER) {
		case Renderers::GL: {
			_PTOS_CREATE_SHADER_FILE_GL;
		}
		default:
			PTOS_CORE_ASSERT(false, "Invalid renderer type");
		}
#elif defined(PTOS_RENDER_GL)
		_PTOS_CREATE_SHADER_FILE_GL;
#endif
		return nullptr;
	}

	Shader* Shader::create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc) {
#if defined(PTOS_RENDER_DYNAMIC)
		switch (CURRENT_RENDERER) {
		case Renderers::GL: {
			_PTOS_CREATE_SHADER_GL;
		}
		default:
			PTOS_CORE_ASSERT(false, "Invalid renderer type");
		}
#elif defined(PTOS_RENDER_GL)
		_PTOS_CREATE_SHADER_GL;
#endif
		return nullptr;
	}
}