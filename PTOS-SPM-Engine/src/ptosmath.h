#pragma once

#include "predefines.h"
#include "mathoperators.h"
#include "vector.h"
#include "matrix.h"
#include "transform.h"

#ifdef PTOS_GLM_MATH
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#endif

namespace PTOS {
	template<typename T> inline T radians(T degrees) { return degrees * 0.017453292519943295; }
	template<typename T> inline T degrees(T radians) { return radians * 57.29577951308232; }

#define PTOS_MAT2_IDENTITY mat2({ {1, 0}, {0, 1} })
#define PTOS_DMAT2_IDENTIDY dmat2({ {1, 0}, {0, 1} })
#define PTOS_MAT3_IDENTITY mat3({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
#define PTOS_DMAT3_IDENTITY dmat3({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
#define PTOS_MAT4_IDENTITY mat4({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}})

#ifdef PTOS_GLM_MATH
	using glm::translate;
	using glm::rotate;
	using glm::scale;
	//using glm::ortho; //can't use glm::ortho in a using statement, maybe because it's defined in an inl file?
	template<typename T> inline glm::mat<4, 4, T, glm::defaultp> ortho(T left, T right, T bottom, T top) {
		return glm::ortho(left, right, bottom, top);
	}
	template<typename T> inline glm::mat<4, 4, T, glm::defaultp> ortho(T left, T right, T bottom, T top, T near, T far) {
		return glm::ortho(left, right, bottom, top, near, far);
	}
	using glm::inverse;
#else

	template<typename T> inline Matrix3<T> translate(const Matrix3<T>& m, const Vector2<T>& v) {
		return m * translate2(v);
	}

	template<typename T> inline Matrix4<T> translate(const Matrix4<T>& m, const Vector3<T>& v) {
		return m * translate3(v);
	}

	template<typename T> inline Matrix3<T> rotate(const Matrix3<T>& m, T angle) {
		return m * rotate2(angle);
	}

	template<typename T> inline Matrix4<T> rotate(const Matrix4<T>& m, T angle, const Vector3<T>& axis) {
		return m * rotate3(axis * angle);
	}
	template<typename T> inline Matrix4<T> rotate(const Matrix4<T>& m, const Vector3<T>& angles) {
		return m * rotate3(angles);
	}

	template<typename T> inline Matrix3<T> scale(const Matrix3<T>& m, const Vector2<T>& v) {
		return m * scale2(v);
	}

	template<typename T> inline Matrix4<T> scale(const Matrix4<T>& m, const Vector3<T>& v) {
		return m * scale3(v);
	}

	template<typename T> inline Matrix4<T> ortho(T left, T right, T top, T bottom, T near, T far) {
		return projectionMatrix(left, right, top, bottom, near, far);
	}

	template<typename T> inline Matrix3<T> inverse(const Matrix3<T>& m) {
		return m.inverse();
	}

	template<typename T> inline Matrix4<T> inverse(const Matrix4<T>& m) {
		return m.inverse();
	}

#endif
}