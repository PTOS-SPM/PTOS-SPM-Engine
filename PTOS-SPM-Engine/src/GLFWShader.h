#pragma once

#include "predefines.h"
#include "Shader.h"

namespace PTOS {
	class GLFWShader : public Shader {
	public:
		static GLFWShader* compile(std::string* src, int* types, size_t count);

		~GLFWShader() { unbind(); del(); }
		void bind() override;
		void unbind() override;
		void upload(const std::string& name, const dmat4& matrix) override;
		void upload(const std::string& name, const mat4& matrix) override;

		inline uint32_t getId() { return id; }
	protected:
		bool loadSource(std::string* src, int* types, size_t count) override;
		void del() override;
	private:
		uint32_t id = 0;
	};
}
