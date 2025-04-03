#pragma once

#include "predefines.h"
#include "ptosmath.h"

#include <string>

namespace PTOS {

	class Shader {
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void upload(const std::string& name, const dmat4& matrix) = 0;
		virtual void upload(const std::string& name, const mat4& matrix) = 0;

	protected:
		virtual bool loadSource(std::string* src, int* types, size_t count) = 0;
		virtual void del() = 0;
	};
}