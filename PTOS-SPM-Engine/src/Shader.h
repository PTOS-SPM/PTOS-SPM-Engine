#pragma once

#include "predefines.h"
#include "ptosmath.h"

#include <string>
#include <unordered_map>

namespace PTOS {

	class Shader {
	public:
		static Shader* create(const std::string& filename);
		static Shader* create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc);

		virtual Shader* copy() = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void upload(const std::string& name, int v) = 0;
		virtual void upload(const std::string& name, float v) = 0;
		virtual void upload(const std::string& name, double v) = 0;

		virtual void upload(const std::string& name, const mat3& matrix) = 0;
		virtual void upload(const std::string& name, const dmat3& matrix) = 0;
		virtual void upload(const std::string& name, const mat4& matrix) = 0;
		virtual void upload(const std::string& name, const dmat4& matrix) = 0;

		virtual void upload(const std::string& name, const vec2& vec) = 0;
		virtual void upload(const std::string& name, const dvec2& vec) = 0;
		virtual void upload(const std::string& name, const vec3& vec) = 0;
		virtual void upload(const std::string& name, const dvec3& vec) = 0;
		virtual void upload(const std::string& name, const vec4& vec) = 0;
		virtual void upload(const std::string& name, const dvec4& vec) = 0;

	protected:
		virtual bool loadSource(std::string* src, int* types, size_t count) = 0;
		virtual void del() = 0;
	};

	struct ShaderLibraryEntry {
		Shader* shader = nullptr;
		bool owned = false;
	};

	class ShaderLibrary {
	public:
		~ShaderLibrary();

		//Adds a new shader to the library. Shader memory is not managed by the library.
		bool add(const std::string& name, Shader* shader);
		//Adds a new shader to the library from the given file. Shader memory is managed by the library.
		Shader* load(const std::string& filePath, std::string& nameOut);
		//Remove the given shader from the library. Does not account for copying. If the shader memory is managed by the library, it will be deleted.
		bool remove(Shader* shader);
		//Remove the shader with the given name from the library. If the shader memory is managed by the library, it will be deleted.
		bool remove(const std::string& name);
		//Get the shader associated with the given name
		Shader* get(const std::string& name) const;
	private:
		std::unordered_map<std::string, ShaderLibraryEntry> shaders;
	};
}