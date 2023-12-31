#pragma once

#include "symbols/math.h"
#include "mathoperators.h"

#include "vector.h"

#include <emmintrin.h>

namespace PTOS {

	template<typename T> struct Matrix2 {
		Matrix2() {}

		Matrix2(const T(&data)[2][2]) {
			memcpy(&this->data, &data, sizeof(T[2][2])); // sizeof(T) * 2 * 2
		}

		Matrix2(Matrix3<T>& mat) {
			memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			memcpy(&data[1], &mat.data[1], sizeof(T[2]));
		}

		Matrix2(Matrix4<T>& mat) {
			memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			memcpy(&data[0], &mat.data[0], sizeof(T[2]));
		}

		T data[2][2]{ {0, 0}, {0, 0} };

		inline T* operator [] (int index) {
			return data[index];
		}

		//Matrix * Matrix

		inline Matrix2<T> operator * (Matrix2<T>& mat) {
			return Matrix2<T>({
				{ mat[0][0] * data[0][0] + mat[1][0] * data[0][1], mat[0][1] * data[0][0] + mat[1][1] * data[0][1] },
				{ mat[1][0] * data[1][1] + mat[0][0] * data[1][0], mat[1][1] * data[1][1] + mat[0][1] * data[1][0] },
			});
		}

		inline Matrix2<T> operator / (Matrix2<T>& mat) {
			return Matrix2<T>({
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][0], data[0][1]), PTOS_ZERO_DIVIDE(mat[0][1], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][1], data[0][1]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[1][1]) + PTOS_ZERO_DIVIDE(mat[0][0], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[1][1]) + PTOS_ZERO_DIVIDE(mat[0][1], data[1][0]) }
			});
		}

		inline Matrix2<T> operator + (Matrix2<T>& mat) {
			return Matrix2<T>({
				{ data[0][0] + mat[0][0], data[0][1] + mat[0][1] },
				{ data[1][0] + mat[1][0], data[1][1] + mat[1][1] }
			});
		}

		inline Matrix2<T> operator - (Matrix2<T>& mat) {
			return Matrix2<T>({
				{ data[0][0] - mat[0][0], data[0][1] - mat[0][1] },
				{ data[1][0] - mat[1][0], data[1][1] - mat[1][1] }
			});
		}

		//Matrix * Vector

		inline Vector2<T> operator * (Vector2<T>& v) {
			return Vector2<T>(
				data[0][0] * v[0] + data[1][0] * v[1],
				data[0][1] * v[0] + data[1][1] * v[1]
			);
		}
		
		inline Vector2<T> operator / (Vector2<T>& v) {
			return Vector2<T>(
				PTOS_ZERO_DIVIDE(data[0][0], v[0]) + PTOS_ZERO_DIVIDE(data[1][0], v[1]),
				PTOS_ZERO_DIVIDE(data[0][1], v[0]) + PTOS_ZERO_DIVIDE(data[1][1], v[1])
			);
		}

		// Matrix * T

		inline Matrix2<T> operator * (T m) {
			return Matrix3<T>({
				{ data[0][0] * m, data[0][1] * m },
				{ data[1][0] * m, data[1][1] * m }
			});
		}

		inline Matrix2<T> operator / (T m) {
			return Matrix3<T>({
				{ PTOS_ZERO_DIVIDE(data[0][0], m), PTOS_ZERO_DIVIDE(data[0][1], m) },
				{ PTOS_ZERO_DIVIDE(data[1][0], m), PTOS_ZERO_DIVIDE(data[1][1], m) }
			});
		}

		inline Matrix2<T> operator + (T m) {
			return Matrix3<T>({
				{ data[0][0] + m, data[0][1] + m },
				{ data[1][0] + m, data[1][1] + m }
			});
		}

		inline Matrix2<T> operator - (T m) {
			return Matrix3<T>({
				{ data[0][0] - m, data[0][1] - m },
				{ data[1][0] - m, data[1][1] - m }
			});
		}
	};

	template <typename T> struct Matrix3 {
		Matrix3() {}

		Matrix3(const T(&data)[3][3]) {
			memcpy(&this->data, &data, sizeof(T[3][3]));
		}

		Matrix3(Matrix2<T>& mat) {
			memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			memcpy(&data[1], &mat.data[1], sizeof(T[2]));
			memcpy(&data[2], &mat.data[2], sizeof(T[2]));
		}

		Matrix3(Matrix4<T>& mat) {
			memcpy(&data[0], &mat.data[0], sizeof(T[3]));
			memcpy(&data[1], &mat.data[1], sizeof(T[3]));
			memcpy(&data[2], &mat.data[2], sizeof(T[3]));
		}

		T data[3][3]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
		
		inline T* operator [] (int index) {
			return data[index];
		}

		//Matrix * Matrix

		inline Matrix3<T> operator * (Matrix3<T>& mat) {
			return Matrix3<T>({
				{ mat[0][0] * data[0][0] + mat[1][0] * data[0][1] + mat[2][0] * data[0][2], mat[0][1] * data[0][0] + mat[1][1] * data[0][1] + mat[2][1] * data[0][2], mat[0][2] * data[0][0] + mat[1][2] * data[0][1] + mat[2][2] * data[0][2] },
				{ mat[1][0] * data[1][1] + mat[2][0] * data[1][2] + mat[0][0] * data[1][0], mat[1][1] * data[1][1] + mat[2][1] * data[1][2] + mat[0][1] * data[1][0], mat[1][2] * data[1][1] + mat[2][2] * data[1][2] + mat[0][2] * data[1][0] },
				{ mat[1][0] * data[2][1] + mat[2][0] * data[2][2] + mat[0][0] * data[2][0], mat[1][1] * data[2][1] + mat[2][1] * data[2][2] + mat[0][1] * data[2][0], mat[1][2] * data[2][1] + mat[2][2] * data[2][2] + mat[0][2] * data[2][0] }
			});
		}
		
		inline Matrix3<T> operator / (Matrix3<T>& mat) {
			return Matrix3<T>({
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][0], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[0][2]), PTOS_ZERO_DIVIDE(mat[0][1], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][1], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[0][2]), PTOS_ZERO_DIVIDE(mat[0][2], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][2], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[0][2]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[1][2]) + PTOS_ZERO_DIVIDE(mat[0][0], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[1][2]) + PTOS_ZERO_DIVIDE(mat[0][1], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[1][2]) + PTOS_ZERO_DIVIDE(mat[0][2], data[1][0]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[2][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][0], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[2][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][1], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[2][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][2], data[2][0]) }
			});
		}

		inline Matrix3<T> operator + (Matrix3<T>& mat) {
			return Matrix3<T>({
				{ data[0][0] + mat[0][0], data[0][1] + mat[0][1], data[0][2] + mat[0][2] },
				{ data[1][0] + mat[1][0], data[1][1] + mat[1][1], data[1][2] + mat[1][2] },
				{ data[2][0] + mat[2][0], data[2][1] + mat[2][1], data[2][2] + mat[2][2] }
			});
		}

		inline Matrix3<T> operator - (Matrix3<T>& mat) {
			return Matrix3<T>({
				{ data[0][0] - mat[0][0], data[0][1] - mat[0][1], data[0][2] - mat[0][2] },
				{ data[1][0] - mat[1][0], data[1][1] - mat[1][1], data[1][2] - mat[1][2] },
				{ data[2][0] - mat[2][0], data[2][1] - mat[2][1], data[2][2] - mat[2][2] }
			});
		}

		//Matrix * Vector

		inline Vector3<T> operator * (Vector3<T>& v) {
			return Vector3<T>(
				data[0][0] * v[0] + data[0][1] * v[1] + data[0][2] * v[2],
				data[1][0] * v[0] + data[1][1] * v[1] + data[1][2] * v[2],
				data[2][0] * v[0] + data[2][1] * v[1] + data[2][2] * v[2]
			);
		}
		
		inline Vector3<T> operator / (Vector3<T>& v) {
			return Vector3<T>(
				PTOS_ZERO_DIVIDE(data[0][0], v[0]) + PTOS_ZERO_DIVIDE(data[0][1], v[1]) + PTOS_ZERO_DIVIDE(data[0][2], v[2]),
				PTOS_ZERO_DIVIDE(data[1][0], v[0]) + PTOS_ZERO_DIVIDE(data[1][1], v[1]) + PTOS_ZERO_DIVIDE(data[1][2], v[2]),
				PTOS_ZERO_DIVIDE(data[2][0], v[0]) + PTOS_ZERO_DIVIDE(data[2][1], v[1]) + PTOS_ZERO_DIVIDE(data[2][2], v[2])
			);
		}

		//Matrix * T

		inline Matrix3<T> operator * (T m) {
			return Matrix3<T>({
				{ data[0][0] * m, data[0][1] * m, data[0][2] * m },
				{ data[1][0] * m, data[1][1] * m, data[1][2] * m },
				{ data[2][0] * m, data[2][1] * m, data[2][2] * m }
				
			});
		}

		inline Matrix3<T> operator / (T m) {
			return Matrix3<T>({
				{ PTOS_ZERO_DIVIDE(data[0][0], m), PTOS_ZERO_DIVIDE(data[0][1], m), PTOS_ZERO_DIVIDE(data[0][2], m) },
				{ PTOS_ZERO_DIVIDE(data[1][0], m), PTOS_ZERO_DIVIDE(data[1][1], m), PTOS_ZERO_DIVIDE(data[1][2], m) },
				{ PTOS_ZERO_DIVIDE(data[2][0], m), PTOS_ZERO_DIVIDE(data[2][1], m), PTOS_ZERO_DIVIDE(data[2][2], m) }
				
			});
		}

		inline Matrix3<T> operator + (T m) {
			return Matrix3<T>({
				{ data[0][0] + m, data[0][1] + m, data[0][2] + m },
				{ data[1][0] + m, data[1][1] + m, data[1][2] + m },
				{ data[2][0] + m, data[2][1] + m, data[2][2] + m }
				
			});
		}

		inline Matrix3<T> operator - (T m) {
			return Matrix3<T>({
				{ data[0][0] - m, data[0][1] - m, data[0][2] - m },
				{ data[1][0] - m, data[1][1] - m, data[1][2] - m },
				{ data[2][0] - m, data[2][1] - m, data[2][2] - m }
			});
		}
	};

	template <typename T> struct Matrix4 {
		Matrix4() {}

		Matrix4(const T(&data)[4][4]) {
			memcpy(&this->data, &data, sizeof(T[4][4]));
		}

		Matrix4(Matrix2<T>& mat) {
			memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			memcpy(&data[1], &mat.data[1], sizeof(T[2]));
		}

		Matrix4(Matrix3<T>& mat) {
			memcpy(&data[0], &mat.data[0], sizeof(T[3]));
			memcpy(&data[1], &mat.data[1], sizeof(T[3]));
			memcpy(&data[2], &mat.data[2], sizeof(T[3]));
		}

		T data[4][4]{ {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };

		inline T* operator [] (int index) {
			return data[index];
		}

		//Matrix * Matrix

		inline Matrix4<T> operator * (Matrix4<T>& mat) {
			return Matrix4<T>({
				{ mat[0][0] * data[0][0] + mat[1][0] * data[0][1] + mat[2][0] * data[0][2] + mat[3][0] * data[0][3], mat[0][1] * data[0][0] + mat[1][1] * data[0][1] + mat[2][1] * data[0][2] + mat[3][1] * data[0][3], mat[0][2] * data[0][0] + mat[1][2] * data[0][1] + mat[2][2] * data[0][2] + mat[3][2] * data[0][3], mat[0][3] * data[0][0] + mat[1][3] * data[0][1] + mat[2][3] * data[0][2] + mat[3][3] * data[0][3] },
				{ mat[1][0] * data[1][1] + mat[2][0] * data[1][2] + mat[3][0] * data[1][3] + mat[0][0] * data[1][0], mat[1][1] * data[1][1] + mat[2][1] * data[1][2] + mat[3][1] * data[1][3] + mat[0][1] * data[1][0], mat[1][2] * data[1][1] + mat[2][2] * data[1][2] + mat[3][2] * data[1][3] + mat[0][2] * data[1][0], mat[1][3] * data[1][1] + mat[2][3] * data[1][2] + mat[3][3] * data[1][3] + mat[0][3] * data[1][0] },
				{ mat[1][0] * data[2][1] + mat[3][0] * data[2][3] + mat[2][0] * data[2][2] + mat[0][0] * data[2][0], mat[1][1] * data[2][1] + mat[3][1] * data[2][3] + mat[2][1] * data[2][2] + mat[0][1] * data[2][0], mat[1][2] * data[2][1] + mat[3][2] * data[2][3] + mat[2][2] * data[2][2] + mat[0][2] * data[2][0], mat[1][3] * data[2][1] + mat[3][3] * data[2][3] + mat[2][3] * data[2][2] + mat[0][3] * data[2][0] },
				{ mat[0][0] * data[3][0] + mat[2][0] * data[3][2] + mat[3][0] * data[3][3] + mat[1][0] * data[3][1], mat[0][1] * data[3][0] + mat[2][1] * data[3][2] + mat[3][1] * data[3][3] + mat[1][1] * data[3][1], mat[0][2] * data[3][0] + mat[2][2] * data[3][2] + mat[3][2] * data[3][3] + mat[1][2] * data[3][1], mat[0][3] * data[3][0] + mat[2][3] * data[3][2] + mat[3][3] * data[3][3] + mat[1][3] * data[3][1] }
			});
		}

		inline Matrix4<T> operator / (Matrix4<T>& mat) {
			return Matrix4<T>({
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][0], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][0], data[0][3]), PTOS_ZERO_DIVIDE(mat[0][1], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][1], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][1], data[0][3]), PTOS_ZERO_DIVIDE(mat[0][2], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][2], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][2], data[0][3]), PTOS_ZERO_DIVIDE(mat[0][3], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][3], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][3], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][3], data[0][3]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][0], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][0], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][1], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][1], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][2], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][2], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][3], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][3], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][3], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][3], data[1][0]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][0], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][0], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][0], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][1], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][1], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][1], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][2], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][2], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][2], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][3], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][3], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][3], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][3], data[2][0]) },
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][0], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][0], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][0], data[3][1]), PTOS_ZERO_DIVIDE(mat[0][1], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][1], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][1], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][1], data[3][1]), PTOS_ZERO_DIVIDE(mat[0][2], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][2], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][2], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][2], data[3][1]), PTOS_ZERO_DIVIDE(mat[0][3], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][3], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][3], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][3], data[3][1]) }
			});
		}

		inline Matrix4<T> operator + (Matrix4<T>& mat) {
			return Matrix4<T>({
				{ data[0][0] + mat[0][0], data[0][1] + mat[0][1], data[0][2] + mat[0][2], data[0][3] + mat[0][3] },
				{ data[1][0] + mat[1][0], data[1][1] + mat[1][1], data[1][2] + mat[1][2], data[1][3] + mat[1][3] },
				{ data[2][0] + mat[2][0], data[2][1] + mat[2][1], data[2][2] + mat[2][2], data[2][3] + mat[2][3] },
				{ data[3][0] + mat[3][0], data[3][1] + mat[3][1], data[3][2] + mat[3][2], data[3][3] + mat[3][3] },
			});
		}

		inline Matrix4<T> operator - (Matrix4<T>& mat) {
			return Matrix4<T>({
				{ data[0][0] - mat[0][0], data[0][1] - mat[0][1], data[0][2] - mat[0][2], data[0][3] - mat[0][3] },
				{ data[1][0] - mat[1][0], data[1][1] - mat[1][1], data[1][2] - mat[1][2], data[1][3] - mat[1][3] },
				{ data[2][0] - mat[2][0], data[2][1] - mat[2][1], data[2][2] - mat[2][2], data[2][3] - mat[2][3] },
				{ data[3][0] - mat[3][0], data[3][1] - mat[3][1], data[3][2] - mat[3][2], data[3][3] - mat[3][3] },
			});
		}

		//Matrix * Vector

		inline Vector4<T> operator * (Vector4<T>& v) {
			return Vector4<T>(
				data[0][0] * v[0] + data[0][1] * v[1] + data[0][2] * v[2] + data[0][3] * v[3],
				data[1][0] * v[0] + data[1][1] * v[1] + data[1][2] * v[2] + data[1][3] * v[3],
				data[2][0] * v[0] + data[2][1] * v[1] + data[2][2] * v[2] + data[2][3] * v[3],
				data[3][0] * v[0] + data[3][1] * v[1] + data[3][2] * v[2] + data[3][3] * v[3]
			);
		}

		inline Vector4<T> operator / (Vector4<T>& v) {
			return Vector4<T>(
				PTOS_ZERO_DIVIDE(data[0][0], v[0]) + PTOS_ZERO_DIVIDE(data[0][1], v[1]) + PTOS_ZERO_DIVIDE(data[0][2], v[2]) + PTOS_ZERO_DIVIDE(data[0][3], v[3]),
				PTOS_ZERO_DIVIDE(data[1][0], v[0]) + PTOS_ZERO_DIVIDE(data[1][1], v[1]) + PTOS_ZERO_DIVIDE(data[1][2], v[2]) + PTOS_ZERO_DIVIDE(data[1][3], v[3]),
				PTOS_ZERO_DIVIDE(data[2][0], v[0]) + PTOS_ZERO_DIVIDE(data[2][1], v[1]) + PTOS_ZERO_DIVIDE(data[2][2], v[2]) + PTOS_ZERO_DIVIDE(data[2][3], v[3]),
				PTOS_ZERO_DIVIDE(data[3][0], v[0]) + PTOS_ZERO_DIVIDE(data[3][1], v[1]) + PTOS_ZERO_DIVIDE(data[3][2], v[2]) + PTOS_ZERO_DIVIDE(data[3][3], v[3])
			);
		}

		//Matrix * T

		inline Matrix4<T> operator * (T m) {
			return Matrix4<T>({
				{ data[0][0] * m, data[0][1] * m, data[0][2] * m, data[0][3] * m },
				{ data[1][0] * m, data[1][1] * m, data[1][2] * m, data[1][3] * m },
				{ data[2][0] * m, data[2][1] * m, data[2][2] * m, data[2][3] * m },
				{ data[3][0] * m, data[3][1] * m, data[3][2] * m, data[3][3] * m }
			});
		}

		inline Matrix4<T> operator / (T m) {
			return Matrix4<T>({
				{ PTOS_ZERO_DIVIDE(data[0][0], m), PTOS_ZERO_DIVIDE(data[0][1], m), PTOS_ZERO_DIVIDE(data[0][2], m), PTOS_ZERO_DIVIDE(data[0][3], m) },
				{ PTOS_ZERO_DIVIDE(data[1][0], m), PTOS_ZERO_DIVIDE(data[1][1], m), PTOS_ZERO_DIVIDE(data[1][2], m), PTOS_ZERO_DIVIDE(data[1][3], m) },
				{ PTOS_ZERO_DIVIDE(data[2][0], m), PTOS_ZERO_DIVIDE(data[2][1], m), PTOS_ZERO_DIVIDE(data[2][2], m), PTOS_ZERO_DIVIDE(data[2][3], m) },
				{ PTOS_ZERO_DIVIDE(data[3][0], m), PTOS_ZERO_DIVIDE(data[3][1], m), PTOS_ZERO_DIVIDE(data[3][2], m), PTOS_ZERO_DIVIDE(data[3][3], m) }
			});
		}

		inline Matrix4<T> operator + (T m) {
			return Matrix4<T>({
				{ data[0][0] + m, data[0][1] + m, data[0][2] + m, data[0][3] + m },
				{ data[1][0] + m, data[1][1] + m, data[1][2] + m, data[1][3] + m },
				{ data[2][0] + m, data[2][1] + m, data[2][2] + m, data[2][3] + m },
				{ data[3][0] + m, data[3][1] + m, data[3][2] + m, data[3][3] + m }
			});
		}

		inline Matrix4<T> operator - (T m) {
			return Matrix4<T>({
				{ data[0][0] - m, data[0][1] - m, data[0][2] - m, data[0][3] - m },
				{ data[1][0] - m, data[1][1] - m, data[1][2] - m, data[1][3] - m },
				{ data[2][0] - m, data[2][1] - m, data[2][2] - m, data[2][3] - m },
				{ data[3][0] - m, data[3][1] - m, data[3][2] - m, data[3][3] - m }
			});
		}
	};

	//Same Instruction, Multiple Data (SIMD) functions
	//cite: https://codereview.stackexchange.com/a/116126

	//TODO: make this work
	mat4 multSIMD(mat4& left, mat4& right) {
		mat4 result;

		__m128d BCx = _mm_load_pd(right[0]);
		__m128d BCy = _mm_load_pd(right[1]);
		__m128d BCz = _mm_load_pd(right[2]);
		__m128d BCw = _mm_load_pd(right[3]);

		double* leftRowPointer = (double*)left.data;
		double* resultRowPointer = (double*)result.data;

#pragma warning(push)
#pragma warning(disable:6305)
		for (int i = 0; i < 4; ++i, leftRowPointer += sizeof(double), resultRowPointer += sizeof(double)) {
			__m128d ARx = _mm_set1_pd(leftRowPointer[0]);
			__m128d ARy = _mm_set1_pd(leftRowPointer[1]);
			__m128d ARz = _mm_set1_pd(leftRowPointer[2]);
			__m128d ARw = _mm_set1_pd(leftRowPointer[3]);

			__m128d X = _mm_mul_pd(ARx, BCx);
			__m128d Y = _mm_mul_pd(ARy, BCy);
			__m128d Z = _mm_mul_pd(ARz, BCz);
			__m128d W = _mm_mul_pd(ARw, BCw);

			__m128d R = _mm_add_pd(X, _mm_add_pd(Y, _mm_add_pd(Z, W)));

			_mm_store_pd(resultRowPointer, R);
		}
#pragma warning(pop)

		return result;
	}
}