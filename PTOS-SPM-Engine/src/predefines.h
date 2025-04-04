#pragma once

#include "Core.h"
#include <stdint.h>

#define PTOS_ZERO_DIVIDE(n, d) (d == 0 ? 0 : (n/d))

#include "glm/glm.hpp"
//GL_FALSE
#define PTOS_GL_TRANSPOSE 0
#else
//GL_TRUE
#define PTOS_GL_TRANSPOSE 1
#endif

namespace PTOS {
	
}

namespace PTOS {
	class PTOS_API Application;

	//math

	template <typename T> PTOS_API struct Vector2;
	template <typename T> PTOS_API struct Vector3;
	template <typename T> PTOS_API struct Vector4;
	template<typename T> PTOS_API struct Matrix2;
	template<typename T> PTOS_API struct Matrix3;
	template<typename T> PTOS_API struct Matrix4;
	class PTOS_API ComponentTransform;

#ifdef PTOS_GLM_MATH
	typedef glm::dvec2 dvec2;
	typedef glm::vec2 vec2;
	typedef glm::dvec3 dvec3;
	typedef glm::vec3 vec3;
	typedef glm::dvec4 dvec4;
	typedef glm::vec4 vec4;
	template<typename T> using Euler = glm::vec<3, T, glm::defaultp>;

	typedef glm::dmat2 dmat2;
	typedef glm::mat2 mat2;
	typedef glm::dmat3 dmat3;
	typedef glm::mat3 mat3;
	typedef glm::dmat4 dmat4;
	typedef glm::mat4 mat4;
#else
	typedef Vector2<double> dvec2;
	typedef Vector2<float> vec2;
	typedef Vector3<double> dvec3;
	typedef Vector3<float> vec3;
	typedef Vector4<double> dvec4;
	typedef Vector4<float> vec4;
	template<typename T> using Euler = Vector3<T>;

	typedef Matrix2<double> dmat2;
	typedef Matrix2<float> mat2;
	typedef Matrix3<double> dmat3;
	typedef Matrix3<float> mat3;
	typedef Matrix4<double> dmat4;
	typedef Matrix4<float> mat4;
#endif


	typedef dvec3 deulr;
	typedef vec3 eulr;
	typedef vec3 rgb;
	typedef vec4 rgba;


	//Input

	namespace Inputs {
		enum PTOS_API Code;
	}
	struct PTOS_API InputState;
	class PTOS_API Input;

	//Rendering

	class PTOS_API Renderer;

	class PTOS_API Shader;

	enum class PTOS_API BuffElmTypeName : uint16_t;
	struct PTOS_API BuffElmType;
	struct PTOS_API BufferElement;
	class PTOS_API BufferLayout;
	class PTOS_API Camera2D;
	class PTOS_API VertexArray;
	class PTOS_API VertexBuffer;
	class PTOS_API IndexBuffer;
	class PTOS_API SceneInfo;
	struct PTOS_API SceneItem;

	//Events

	struct PTOS_API Event;
	struct PTOS_API EventContext;
	struct PTOS_API EventResult;
	struct PTOS_API EventQueueNode;
	struct PTOS_API EventListener;
	struct PTOS_API EventListenerNode;
	enum class PTOS_API EventResultState : uint8_t;
	typedef EventResult (*EventListenerFunc)(const EventContext&);
	typedef uint64_t EventType;
	class PTOS_API EventLayer;
	struct PTOS_API EventLayerNode;
	class PTOS_API EventSystem;

	namespace EventTypes {
		enum PTOS_API BuiltinEventTypes : EventType;
	}

	//Window

	class PTOS_API Window;
	struct PTOS_API WindowSize;
	struct PTOS_API WindowProperties;
	class PTOS_API WindowRenderer;

	//GLFW Overrides

	class PTOS_API GLFWIndexBuffer;
	class PTOS_API GLFWRenderer;
	class PTOS_API GLFWShader;
	class PTOS_API GLFWVertexBuffer;

	class PTOS_API GLFWWindowRenderer;
}