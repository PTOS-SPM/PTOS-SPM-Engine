#pragma once

#include "predefines.h"
#include "ptosmath.h"

#include <string>

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
}