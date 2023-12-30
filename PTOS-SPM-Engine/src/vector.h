#pragma once

#include "symbols/math.h"
#include "mathoperators.h"

#include <cmath>

//assume radians for any angles

namespace PTOS {

	//forward declare vectors to allow access to eachother

	template<typename T> struct Vector2 {
		static inline Vector2<T> up() { return Vector2<T>(0.0, 1.0); }
		static inline Vector2<T> down() { return Vector2<T>(0.0, -1.0); }
		static inline Vector2<T> right() { return Vector2<T>(1.0, 0.0); }
		static inline Vector2<T> left() { return Vector2<T>(-1.0, 0.0); }
		static inline Vector2<T> one() { return Vector2<T>(1.0, 1.0); }
		
		static inline T angle(Vector2<T>& lv, Vector2<T>& rv) {
			return atan2(rv[1] * lv[0] - rv[0] * lv[1], rv[0] * lv[0] + rv[1] * lv[1]);
		}

		static inline T distance(Vector2<T>& lv, Vector2<T>& rv) {
			return sqrt((lv[1] - rv[1]) * (lv[1] - rv[1]) + (lv[0] - rv[0]) * (lv[0] - rv[0]));
		}

		static inline T dot(Vector2<T>& lv, Vector2<T>& rv) {
			return lv[0] * rv[0] + lv[1] * rv[1];
		}

		Vector2() {}

		Vector2(T x, T y) {
			data[0] = x;
			data[1] = y;
		}

		Vector2(const T(&data)[2]) {
			memcpy(&this->data, &data, sizeof(T) * 2);
		}

		Vector2(T* data, size_t len) {
			memcpy(&this->data, data, sizeof(T) * (len < 2 ? len : 2));
		}

		//conversions

		Vector2(Vector3<T>& v) {
			memcpy(&data, &v.data, sizeof(T) * 2);
		}

		Vector2(Vector4<T>& v) {
			memcpy(&data, &v.data, sizeof(T) * 2);
		}

		T data[2]{ 0, 0 };

		inline T& x() { return data[0]; }
		inline T& y() { return data[1]; }

		inline T operator [] (int index) {
			return data[index];
		}

		inline Vector2<T> operator * (T m) {
			return Vector2<T>(data[0] * m, data[1] * m);
		}

		inline Vector2<T> operator / (T m) {
			return Vector2<T>(PTOS_ZERO_DIVIDE(data[0], m), PTOS_ZERO_DIVIDE(data[1], m));
		}

		inline Vector2<T> operator + (T m) {
			return Vector2<T>(data[0] + m, data[1] + m);
		}

		inline Vector2<T> operator - (T m) {
			return Vector2<T>(data[0] - m, data[1] - m);
		}

		inline Vector2<T> operator * (Vector2<T>& v) {
			return Vector2<T>(data[0] * v[0], data[1] * v[1]);
		}

		inline Vector2<T> operator / (Vector2<T>& v) {
			return Vector2<T>(PTOS_ZERO_DIVIDE(data[0], v[0]), PTOS_ZERO_DIVIDE(data[1], v[1]));
		}

		inline Vector2<T> operator + (Vector2<T>& v) {
			return Vector2<T>(data[0] + v[0], data[1] + v[1]);
		}
		
		inline Vector2<T> operator - (Vector2<T>& v) {
			return Vector2<T>(data[0] - v[0], data[1] - v[1]);
		}

		inline bool operator == (Vector2<T> v) {
			return data[0] == v[0] && data[1] == v[1];
		}
		
		inline T magnitude() {
			return sqrt(data[0] * data[0] + data[1] * data[1]);
		}

		Vector2<T> normalize() {
			T mag = magnitude();
			return mag == 0 ? Vector2<T>() : *this / mag;
		}

		inline Vector2<T> perpendicular() {
			return Vector2<T>(-data[1], data[0]);
		}

	};

	template<typename T> struct Vector3 {
		static inline Vector3<T> up() { return Vector3<T>(0.0, 1.0, 0.0); }
		static inline Vector3<T> down() { return Vector3<T>(0.0, -1.0, 0.0); }
		static inline Vector3<T> right() { return Vector3<T>(1.0, 0.0, 0.0); }
		static inline Vector3<T> left() { return Vector3<T>(-1.0, 0.0, 0.0); }
		static inline Vector3<T> forward() { return Vector3<T>(0.0, 0.0, 1.0); }
		static inline Vector3<T> back() { return Vector3<T>(0.0, 0.0, -1.0); }
		static inline Vector3<T> one() { return Vector3<T>(1.0, 1.0, 1.0); }

		static inline T angle(Vector3<T>& lv, Vector3<T>& rv) {
			return acos(dot(lv, rv) / (lv.magnitude() * rv.magnitude()));
		}

		static inline Vector3<T> cross(Vector3<T>& lv, Vector3<T>& rv) {
			return Vector3<T>(lv[1] * rv[2] - lv[2] * rv[1], lv[2] * rv[0] - lv[0] * rv[2], lv[0] * rv[1] - lv[1] * rv[0]);
		}

		static inline T distance(Vector3<T>& lv, Vector3<T>& rv) {
			return sqrt((lv[0] - rv[0]) * (lv[0] - rv[0]) + (lv[1] - rv[1]) * (lv[1] - rv[1]) + (lv[2] - rv[2]) * (lv[2] - rv[2]));
		}

		static inline T dot(Vector3<T>& lv, Vector3<T>& rv) {
			return lv[0] * rv[0] + lv[1] * rv[1] + lv[2] * rv[2];
		}

		Vector3() {}

		Vector3(T x, T y, T z) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}

		Vector3(const T(&data)[3]) {
			memcpy(&this->data, &data, sizeof(T) * 3);
		}

		Vector3(T* data, size_t len) {
			memcpy(&this->data, data, sizeof(T) * (len < 3 ? len : 3));
		}

		//conversions

		Vector3(Vector2<T>& v, T z) {
			memcpy(&data, &v.data, sizeof(T) * 2);
			data[2] = z;
		}

		Vector3(Vector2<T>& v) : Vector3(v, 0) {}

		Vector3(Vector4<T>& v) {
			memcpy(&data, &v.data, sizeof(T) * 3);
		}

		T data[3]{ 0, 0, 0 };

		inline T& x() { return data[0]; }
		inline T& y() { return data[1]; }
		inline T& z() { return data[2]; }
		//if using Vector3 as a Vector2 with a w component
		inline T& w() { return data[2]; }

		inline T& r() { return data[0]; }
		inline T& g() { return data[1]; }
		inline T& b() { return data[2]; }

		inline T operator [] (int index) {
			return data[index];
		}

		inline Vector3<T> operator * (T m) {
			return Vector3<T>(data[0] * m, data[1] * m, data[2] * m);
		}

		inline Vector3<T> operator / (T m) {
			return Vector3<T>(PTOS_ZERO_DIVIDE(data[0], m), PTOS_ZERO_DIVIDE(data[1], m), PTOS_ZERO_DIVIDE(data[2], m));
		}

		inline Vector3<T> operator + (T m) {
			return Vector3<T>(data[0] + m, data[1] + m, data[2] + m);
		}

		inline Vector3<T> operator - (T m) {
			return Vector3<T>(data[0] - m, data[1] - m, data[2] - m);
		}

		inline Vector3<T> operator * (Vector3<T>& v) {
			return Vector3<T>(data[0] * v[0], data[1] * v[1], data[2] * v[2]);
		}

		inline Vector3<T> operator / (Vector3<T>& v) {
			return Vector3<T>(PTOS_ZERO_DIVIDE(data[0], v[0]), PTOS_ZERO_DIVIDE(data[1], v[1]), PTOS_ZERO_DIVIDE(data[2], v[2]));
		}

		inline Vector3<T> operator + (Vector3<T>& v) {
			return Vector3<T>(data[0] + v[0], data[1] + v[1], data[2] + v[2]);
		}

		inline Vector3<T> operator - (Vector3<T>& v) {
			return Vector3<T>(data[0] - v[0], data[1] - v[1], data[2] - v[2]);
		}

		inline bool operator == (Vector3<T> v) {
			return data[0] == v[0] && data[1] == v[1] && data[2] == v[2];
		}

		inline T magnitude() {
			return sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
		}

		Vector3<T> normalize() {
			T mag = magnitude();
			return mag == 0 ? Vector3<T>() : *this / mag;
		}

	};

	template<typename T> struct Vector4 {
		static inline Vector4<T> up() { return Vector4<T>(0.0, 1.0, 0.0, 0.0); }
		static inline Vector4<T> down() { return Vector4<T>(0.0, -1.0, 0.0, 0.0); }
		static inline Vector4<T> right() { return Vector4<T>(1.0, 0.0, 0.0, 0.0); }
		static inline Vector4<T> left() { return Vector4<T>(-1.0, 0.0, 0.0, 0.0); }
		static inline Vector4<T> forward() { return Vector4<T>(0.0, 0.0, 1.0, 0.0); }
		static inline Vector4<T> back() { return Vector4<T>(0.0, 0.0, -1.0, 0.0); }
		static inline Vector4<T> one() { return Vector4<T>(1.0, 1.0, 1.0, 1.0); }

		static inline T angle(Vector4<T>& lv, Vector4<T>& rv) {
			return acos(dot(lv, rv) / (lv.magnitude() * rv.magnitude()));
		}

		static inline T distance(Vector4<T>& lv, Vector4<T>& rv) {
			return sqrt((lv[0] - rv[0]) * (lv[0] - rv[0]) + (lv[1] - rv[1]) * (lv[1] - rv[1]) + (lv[2] - rv[2]) * (lv[2] - rv[2]) + (lv[3] - rv[3]) * (lv[3] - rv[3]));
		}

		static inline T dot(Vector4<T>& lv, Vector4<T>& rv) {
			return lv[0] * rv[0] + lv[1] * rv[1] + lv[2] * rv[2] + lv[3] * rv[3];
		}

		Vector4() {}

		Vector4(T x, T y, T z, T w) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}

		Vector4(const T(&data)[4]) {
			memcpy(&this->data, &data, sizeof(T) * 4);
		}

		Vector4(T* data, size_t len) {
			memcpy(&this->data, data, sizeof(T) * (len < 4 ? len : 4));
		}

		//conversions

		Vector4(Vector2<T>& v, T z, T w) {
			memcpy(&data, &v.data, sizeof(T) * 2);
			data[2] = z;
			data[3] = w;
		}

		Vector4(Vector2<T>& v, T z) : Vector4(v, z, 0) {}
		Vector4(Vector2<T>& v) : Vector4(v, 0, 0) {}

		Vector4(Vector3<T>& v, T w) {
			memcpy(&data, &v.data, sizeof(T) * 3);
			data[3] = w;
		}

		Vector4(Vector3<T>& v) : Vector4(v, 0) {}

		T data[4]{ 0, 0, 0, 0 };

		inline T& x() { return data[0]; }
		inline T& y() { return data[1]; }
		inline T& z() { return data[2]; }
		inline T& w() { return data[3]; }

		inline T& r() { return data[0]; }
		inline T& g() { return data[1]; }
		inline T& b() { return data[2]; }
		inline T& a() { return data[3]; }

		inline T operator [] (int index) {
			return data[index];
		}

		inline Vector4<T> operator * (T m) {
			return Vector4<T>(data[0] * m, data[1] * m, data[2] * m, data[3] * m);
		}

		inline Vector4<T> operator / (T m) {
			return Vector4<T>(PTOS_ZERO_DIVIDE(data[0], m), PTOS_ZERO_DIVIDE(data[1], m), PTOS_ZERO_DIVIDE(data[2], m), PTOS_ZERO_DIVIDE(data[3], m));
		}

		inline Vector4<T> operator + (T m) {
			return Vector4<T>(data[0] + m, data[1] + m, data[2] + m, data[3] + m);
		}

		inline Vector4<T> operator - (T m) {
			return Vector4<T>(data[0] - m, data[1] - m, data[2] - m, data[3] - m);
		}

		inline Vector4<T> operator * (Vector4<T>& v) {
			return Vector4<T>(data[0] * v[0], data[1] * v[1], data[2] * v[2], data[3] * v[3]);
		}

		inline Vector4<T> operator / (Vector4<T>& v) {
			return Vector4<T>(PTOS_ZERO_DIVIDE(data[0], v[0]), PTOS_ZERO_DIVIDE(data[1], v[1]), PTOS_ZERO_DIVIDE(data[2], v[2]), PTOS_ZERO_DIVIDE(data[3], v[3]));
		}

		inline Vector4<T> operator + (Vector4<T>& v) {
			return Vector4<T>(data[0] + v[0], data[1] + v[1], data[2] + v[2], data[3] + v[3]);
		}

		inline Vector4<T> operator - (Vector4<T>& v) {
			return Vector4<T>(data[0] - v[0], data[1] - v[1], data[2] - v[2], data[3] - v[3]);
		}

		inline bool operator == (Vector4<T> v) {
			return data[0] == v[0] && data[1] == v[1] && data[2] == v[2] && data[3] == v[3];
		}

		inline T magnitude() {
			return sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
		}

		Vector4<T> normalize() {
			T mag = magnitude();
			return mag == 0 ? Vector4<T>() : *this / mag;
		}
	};
}
