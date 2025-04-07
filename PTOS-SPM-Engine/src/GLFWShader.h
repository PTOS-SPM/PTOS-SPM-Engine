#pragma once

#include "predefines.h"
#include "Shader.h"

namespace PTOS {
	class GLFWShader : public Shader {
	public:
		static GLFWShader* compile(std::string* src, int* types, size_t count);
		static size_t readFromFile(const std::string& path, std::string** srcOut, int** typesOut);

		~GLFWShader() { unbind(); del(); }

		Shader* copy() override;

		void bind() override;
		void unbind() override;

		void upload(const std::string& name, int v) override;
		void upload(const std::string& name, float v) override;
		void upload(const std::string& name, double v) override;

		void upload(const std::string& name, const mat3& matrix) override;
		void upload(const std::string& name, const dmat3& matrix) override;
		void upload(const std::string& name, const mat4& matrix) override;
		void upload(const std::string& name, const dmat4& matrix) override;

		void upload(const std::string& name, const vec2& vec) override;
		void upload(const std::string& name, const dvec2& vec) override;
		void upload(const std::string& name, const vec3& vec) override;
		void upload(const std::string& name, const dvec3& vec) override;
		void upload(const std::string& name, const vec4& vec) override;
		void upload(const std::string& name, const dvec4& vec) override;

		inline uint32_t getId() { return id; }
	protected:
		bool loadSource(std::string* src, int* types, size_t count) override;
		void del() override;
	private:
		std::string* loadedSrc = nullptr;
		int* loadedTypes = nullptr;
		size_t loadedCount = 0;
		uint32_t id = 0;
	};
}
