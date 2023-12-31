#pragma once

#include "symbols/window.h"
#include <string>

#define PTOS_OVERRIDE_SHADER_METHODS_PUBLIC(name) \
		~name() { unbind(); del(); } \
		void bind() override; \
		void unbind() override; \

#define PTOS_OVERRIDE_SHADER_METHODS_PROTECTED() \
		bool loadSource(std::string* src, int* types, size_t count) override; \
		void del() override; \
		

namespace PTOS {

	class Shader {
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

	protected:
		virtual bool loadSource(std::string* src, int* types, size_t count) = 0;
		virtual void del() = 0;
	};
}