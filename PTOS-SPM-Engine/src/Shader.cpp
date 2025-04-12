#include "Log.h"
#include "Shader.h"

#ifdef PTOS_RENDER_DYNAMIC
#include "Renderer.h"
#endif

#if defined(PTOS_RENDER_GL) || defined(PTOS_RENDER_DYNAMIC)
#include "glad/glad.h"
#include "GLFWShader.h"
#endif

#include <sstream>


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

	ShaderLibrary::~ShaderLibrary() {
		for (auto it = shaders.begin(); it != shaders.end(); it++) {
			if (it->second.owned)
				delete it->second.shader;
		}
		shaders.clear();
	}

	bool ShaderLibrary::add(const std::string& name, Shader* shader) {
		auto entry = shaders.find(name);
		if (entry != shaders.end())
			return false;
		entry->second = ShaderLibraryEntry{ shader, false };
		return true;
	}

	Shader* ShaderLibrary::load(const std::string& filePath, std::string& nameOut) {
		Shader* shader = Shader::create(filePath);
		if (shader == nullptr)
			return nullptr;

		size_t start = filePath.find_last_of("/\\") + 1; //if std::string::npos, then max(size_t) + 1 == 0 (overflow)
		size_t end = filePath.rfind('.');
		if (end == std::string::npos)
			end = filePath.size() - start;
		std::string nameBase = filePath.substr(start, end - start);
		std::string shaderName = nameBase;
		
		size_t i = 0;
		auto entry = shaders.find(shaderName);
		while (entry != shaders.end()) {
			shaderName = nameBase + std::to_string(i);
			entry = shaders.find(shaderName);
		}

		shaders[shaderName] = ShaderLibraryEntry{ shader, true };
		return shader;
	}

	bool ShaderLibrary::remove(Shader* shader) {
		bool has = false;
		for (auto it = shaders.begin(); it != shaders.end();) {
			if (it->second.shader == shader) {
				shaders.erase(it);
				if (!has)
					has = true;
			}
			else it++;
		}
		return has;
	}

	bool ShaderLibrary::remove(const std::string& name) {
		return shaders.erase(name);
	}

	Shader* ShaderLibrary::get(const std::string& name) const {
		auto entry = shaders.find(name);
		if (entry == shaders.end())
			return nullptr;
		return entry->second.shader;
	}

	bool ShaderLibrary::change(const std::string& oldname, const std::string& newname) {
		auto entry = shaders.find(oldname);
		if (entry == shaders.end() || shaders.find(newname) != shaders.end())
			return false;
		ShaderLibraryEntry libraryEntry = entry->second;
		shaders.erase(entry);
		shaders[newname] = libraryEntry;
		return true;
	}
}