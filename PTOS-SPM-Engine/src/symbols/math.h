#pragma once

#include "Core.h"

#define PTOS_ZERO_DIVIDE(n, d) (d == 0 ? 0 : (n/d))

namespace PTOS {

	template <typename T> struct Vector2;
	template <typename T> struct Vector3;
	template <typename T> struct Vector4;
	typedef Vector2<double> vec2;
	typedef Vector2<float> vec2f;
	typedef Vector3<double> vec3;
	typedef Vector3<float> vec3f;
	typedef Vector4<double> vec4;
	typedef Vector4<float> vec4f;
	typedef vec3 euler;

	template<typename T> struct Matrix2;
	template<typename T> struct Matrix3;
	template<typename T> struct Matrix4;
	typedef Matrix2<double> mat2;
	typedef Matrix2<float> mat2f;
	typedef Matrix3<double> mat3;
	typedef Matrix3<float> mat3f;
	typedef Matrix4<double> mat4;
	typedef Matrix4<float> mat4f;
}