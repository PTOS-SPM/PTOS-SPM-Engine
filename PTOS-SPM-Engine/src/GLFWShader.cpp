#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "GLFWShader.h"
#include "Log.h"

namespace PTOS {

	GLFWShader* GLFWShader::compile(std::string* src, int* types, size_t count) {
		GLFWShader* shader = new GLFWShader();
		PTOS_CORE_VERIFY(shader->loadSource(src, types, count), "GLFW Shader Load Error");
		return shader;
	}

	void GLFWShader::bind() {
		glUseProgram(id);
	}

	void GLFWShader::unbind() {
		glUseProgram(0); //shader program id of 0 means bind to no program
	}

	//cite: https://www.khronos.org/opengl/wiki/Shader_Compilation

	bool GLFWShader::loadSource(std::string* src, int* types, size_t count) {

		//shader id array
		GLuint* shaders = (GLuint*)calloc(count, sizeof(GLuint));
		if (shaders == nullptr) {
			PTOS_CORE_ERR("Failed calloc");
			return false;
		}

		//compile each shader

		for (size_t i = 0; i < count; i++) {

			GLuint shaderId = glCreateShader(types[i]);

			const GLchar* source = (const GLchar*)src[i].c_str();
			glShaderSource(shaderId, 1, &source, 0);

			glCompileShader(shaderId);

			GLint isCompiled = 0;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

				//if a stackoverlfow happens, it was destined to happen ¯\_("/)_/¯
#pragma warning(push)
#pragma warning(disable:6255)
#pragma warning(disable:6263)
				char* infoLog = (char*)alloca(sizeof(char) * maxLength);
#pragma warning(pop)
				glGetShaderInfoLog(shaderId, maxLength, &maxLength, infoLog);
				PTOS_CORE_ERR("GLFW Shader {0} Compile Error: {1}", shaderId, infoLog);
				
				//delete all shaders made before this one; if one is rotten, then discard all
				for (GLuint sindex = 0; sindex < i; sindex++)
					glDeleteShader(shaders[sindex]);

				glDeleteShader(shaderId);

				free(shaders);

				return false;
			}

			shaders[i] = shaderId;
		}

		id = glCreateProgram();
		for (size_t i = 0; i < count; i++)
			glAttachShader(id, shaders[i]);

		glLinkProgram(id);
		GLint isLinked = 0;
		glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
#pragma warning(push)
#pragma warning(disable:6255)
			char* infoLog = (char*)alloca(sizeof(char) * maxLength);
#pragma warning(pop)
			glGetProgramInfoLog(id, maxLength, &maxLength, infoLog);
			PTOS_CORE_ERR("GLFW Program {0} Link Error: {1}", id, infoLog);
		}

		//below behavior is common between link success and failure

		//detach and delete shaders to free memory and (if link succeeded) make shader program deletion easier later
		//cite: https://stackoverflow.com/a/9117411

		for (size_t i = 0; i < count; i++) {
			glDetachShader(id, shaders[i]);
			//glDeleteShader(shaders[i]);
		}

		free(shaders);

		//resume failure-specific behavior
		if (isLinked == GL_FALSE) {
			glDeleteProgram(id);
			id = 0;
			return false;
		}
		else return true;
	}

	
	void GLFWShader::del() {
		glDeleteProgram(id);
	}
}
