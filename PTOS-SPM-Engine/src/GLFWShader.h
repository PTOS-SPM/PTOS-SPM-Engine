#pragma once

#include "Shader.h"

namespace PTOS {
	class GLFWShader : public Shader {
	public:
		static GLFWShader* compile(std::string* src, int* types, size_t count);

		PTOS_OVERRIDE_SHADER_METHODS_PUBLIC(GLFWShader)

		inline unsigned int getId() { return id; }
	protected:
		PTOS_OVERRIDE_SHADER_METHODS_PROTECTED()
	private:
		unsigned int id = 0;
	};
}
