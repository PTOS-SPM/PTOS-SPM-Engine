#pragma once

#include "Core.h"

namespace PTOS {

	//Window Data

	struct PTOS_API WindowSize;
	struct PTOS_API WindowProperties;

	//Event System

	class PTOS_API WindowEvent;
	enum PTOS_API WindowEventType;

	//Shader

	class PTOS_API Shader;

	//Rendering Buffers

	enum class PTOS_API BufferElementTypeName : unsigned char;
	struct PTOS_API BuffElmType;
	struct PTOS_API BufferElement;
	class PTOS_API BufferLayout;
	class PTOS_API VertexArray;
	class PTOS_API VertexBuffer;
	class PTOS_API IndexBuffer;

	//Window

	class PTOS_API Window;
	class PTOS_API WindowRenderer;

	//GLFW

	class PTOS_API GLFWIndexBuffer;
	class PTOS_API GLFWRenderer;
	class PTOS_API GLFWShader;
	class PTOS_API GLFWVertexBuffer;
}
