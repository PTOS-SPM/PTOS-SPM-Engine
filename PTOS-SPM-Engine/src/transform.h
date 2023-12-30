#pragma once

#include "vector.h"
#include "matrix.h"

namespace PTOS {
	template<typename T> inline Matrix3<T> identity2() {
		return Matrix3<T>({
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		});
	}

	template<typename T> inline Matrix3<T> translate2(T x, T y) {
		return Matrix3<T>({
			{1, 0, x},
			{0, 1, y},
			{0, 0, 1}
		});
	}

	template<typename T> inline Matrix3<T> translate2(Vector2<T> v) {
		return translate2<T>(v.x(), v.y());
	}

	template<typename T> Matrix3<T> rotate2(double r) {
		if (r == 0)
			return identity2<T>();
		else if (r > 0)
			return Matrix3<T>({
				{(T)cos(r), (T)sin(r), 0},
				{(T)(-sin(r)), (T)(cos(r), 0},
				{0, 0, 1}
			});
		else
			return Matrix3<T>({
				{(T)cos(r), (T)(-sin(r)), 0},
				{(T)sin(r), (T)cos(r), 0},
				{0, 0, 1}
			}));
	}

	template<typename T> inline Matrix3<T> scale2(T x, T y) {
		return Matrix3<T>({
			{x, 0, 0},
			{0, y, 0},
			{0, 0, 1}
		});
	}

	template<typename T> inline Matrix3<T> scale2(Vector2<T> v) {
		return scale2<T>(v.x(), v.y());
	}

	template<typename T> inline Matrix4<T> identity3() {
		return Matrix4<T>({
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		});
	}

	template<typename T> inline Matrix4<T> translate3(T x, T y, T z) {
		return Matrix4<T>({
			{1, 0, 0, x},
			{0, 1, 0, y},
			{0, 0, 1, z},
			{0, 0, 0, 1}
		});
	}

	template<typename T> inline Matrix4<T> translate3(Vector3<T> v) {
		return translate3<T>(v.x(), v.y(), v.z());
	}

	template<typename T> inline Matrix4<T> rotate3(euler r) {
		return Matrix4<T>({
			{cos(r.z()) * cos(r.y()), cos(r.z()) * sin(r.y()) * sin(r.x()) - sin(r.z()) * cos(r.x()), cos(r.z()) * sin(r.y()) * cos(r.x()) + sin(r.z()) * sin(r.x()), 0},
			{sin(r.z()) * cos(r.y()), sin(r.z()) * sin(r.y()) * sin(r.x()) + cos(r.z()) * cos(r.x()), sin(r.z()) * sin(r.y()) * cos(r.x()) - cos(r.z()) * sin(r.x()), 0},
			{-sin(r.y()), cos(r.y()) * sin(r.x()), cos(r.y()) * cos(r.x()), 0},
			{0, 0, 0, 1}
		});
	}

	template<typename T> inline Matrix4<T> scale3(T x, T y, T z) {
		return Matrix4<T>({
			{x, 0, 0, 0},
			{0, y, 0, 0},
			{0, 0, z, 0},
			{0, 0, 0, 1}
		});
	}

	template<typename T> inline Matrix4<T> scale3(Vector3<T> v) {
		return scale3<T>(v.x(), v.y(), v.z());
	}
}
