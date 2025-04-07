#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <vector>

#include "GLFWShader.h"
#include "Log.h"

namespace PTOS {

	GLFWShader* GLFWShader::compile(std::string* src, int* types, size_t count) {
		GLFWShader* shader = new GLFWShader();
		PTOS_CORE_VERIFY(shader->loadSource(src, types, count), "GLFW Shader Load Error");
		return shader;
	}

	//make sure to free srcOut and typesOut
	size_t GLFWShader::readFromFile(const std::string& path, std::string** srcOut, int** typesOut) {
		std::ifstream inFile(path, std::ios::in, std::ios::binary);
		PTOS_ASSERT(inFile, "Failed to open file");
		std::string contents;

		inFile.seekg(0, std::ios::end);
		contents.resize(inFile.tellg());
		inFile.seekg(0, std::ios::beg);
		inFile.read(&contents[0], contents.size());

		inFile.close();

		std::vector<size_t> positions;
		const char* typeToken = "#type";
		size_t typeTokenLength = std::strlen(typeToken);

		size_t currentPos = 0;
		do {
			currentPos = contents.find(typeToken, currentPos);
			if (currentPos == std::string::npos)
				break;
			size_t afterToken = currentPos + typeTokenLength;
			if (!(contents[afterToken] == ' ' || contents[afterToken] == '\t')) {
				currentPos = contents.find_first_of("\r\n", currentPos);
				if (currentPos == std::string::npos)
					break;
				currentPos++;
				continue;
			}
			size_t eol = contents.find_first_of("\r\n", currentPos);
			PTOS_CORE_ASSERT(eol != std::string::npos, "Syntax Error: EOF");

			positions.push_back(afterToken+1);
			positions.push_back(eol);
			currentPos = eol + 1;

		} while (currentPos != std::string::npos);

		size_t count = positions.size() / 2;
		if (count == 0)
			return 0;
		std::string* srcs = new std::string[count];
		int* types = new int[count];

		for (auto it = positions.begin(); it != positions.end(); it += 2) {
			size_t beginType = *it, eol = *(it+1);
			bool isEnd = (it + 2) >= positions.end();

			std::string typeName = contents.substr(beginType, eol - beginType);
			typeName.erase(typeName.begin(), std::find_if(typeName.begin(), typeName.end(), [](unsigned char ch) { return !std::isspace(ch); }));
			typeName.erase(std::find_if(typeName.rbegin(), typeName.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), typeName.end());
			PTOS_CORE_ASSERT(typeName.size() != 0, "Syntax Error: missing shader type name");
			std::transform(typeName.begin(), typeName.end(), typeName.begin(), ::tolower);

			int type;
			if (typeName == "vertex")
				type = GL_VERTEX_SHADER;
			else if (typeName == "fragment" || typeName == "pixel")
				type = GL_FRAGMENT_SHADER;
			else
				PTOS_CORE_ASSERT(false, "Shader Type Error: invalid GL shader type");

			std::string src;
			if (isEnd)
				src = contents.substr(eol + 1);
			else
				src = contents.substr(eol + 1, *(it + 2) - eol - 2 - (typeTokenLength));

			size_t index = (it - positions.begin()) / 2;
			srcs[index] = src;
			types[index] = type;
		}

		*srcOut = srcs;
		*typesOut = types;

		return count;
	}

	Shader* GLFWShader::copy() {
		GLFWShader* shader = new GLFWShader();
		if (loadedCount)
			shader->loadSource(loadedSrc, loadedTypes, loadedCount);
		return shader;
	}

	void GLFWShader::bind() {
		glUseProgram(id);
	}

	void GLFWShader::unbind() {
		glUseProgram(0); //shader program id of 0 means bind to no program
	}

	void GLFWShader::upload(const std::string& name, int v) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform1i(location, v);
	}

	void GLFWShader::upload(const std::string& name, float v) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform1f(location, v);
	}

	void GLFWShader::upload(const std::string& name, double v) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform1d(location, v);
	}

	void GLFWShader::upload(const std::string& name, const mat3& matrix) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniformMatrix3fv(location, 1, PTOS_GL_TRANSPOSE, (GLfloat*)&matrix[0][0]);
	}

	void GLFWShader::upload(const std::string& name, const dmat3& matrix) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniformMatrix3dv(location, 1, PTOS_GL_TRANSPOSE, (GLdouble*)&matrix[0][0]);
	}

	void GLFWShader::upload(const std::string& name, const mat4& matrix) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniformMatrix4fv(location, 1, PTOS_GL_TRANSPOSE, (GLfloat*)&matrix[0][0]);
	}

	void GLFWShader::upload(const std::string& name, const dmat4& matrix) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniformMatrix4dv(location, 1, PTOS_GL_TRANSPOSE, (GLdouble*)&matrix[0][0]);
	}

	void GLFWShader::upload(const std::string& name, const vec2& vec) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform2f(location, vec[0], vec[1]);
	}

	void GLFWShader::upload(const std::string& name, const dvec2& vec) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform2d(location, vec[0], vec[1]);
	}

	void GLFWShader::upload(const std::string& name, const vec3& vec) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform3f(location, vec[0], vec[1], vec[2]);
	}

	void GLFWShader::upload(const std::string& name, const dvec3& vec) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform3d(location, vec[0], vec[1], vec[2]);
	}

	void GLFWShader::upload(const std::string& name, const vec4& vec) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
	}

	void GLFWShader::upload(const std::string& name, const dvec4& vec) {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform4d(location, vec[0], vec[1], vec[2], vec[3]);
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
		
		loadedSrc = new std::string[count];
		loadedTypes = new int[count];

		for (size_t i = 0; i < count; i++)
			loadedSrc[i] = src[i];
		std::memcpy(loadedTypes, types, sizeof(types[0]) * count);
		loadedCount = count;

		
		return true;
	}


	void GLFWShader::del() {
		glDeleteProgram(id);
		delete[] loadedSrc;
		delete[] loadedTypes;
		id = 0;
		loadedSrc = nullptr;
		loadedTypes = nullptr;
		loadedCount = 0;
	}
}
