#pragma once

#include "predefines.h"
#include "mathoperators.h"

#include "vector.h"

#include <cstring>

namespace PTOS {

	template<typename T> struct Matrix2 {
		static inline Matrix2 identity() {
			return Matrix2({
				{1, 0},
				{0, 1}
			});
		}

		Matrix2() {}

		Matrix2(const T(&data)[2][2]) {
			std::memcpy(&this->data, &data, sizeof(T[2][2])); // sizeof(T) * 2 * 2
		}

		Matrix2(const Matrix3<T>& mat) {
			std::memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			std::memcpy(&data[1], &mat.data[1], sizeof(T[2]));
			valid = mat.valid;
		}

		Matrix2(const Matrix4<T>& mat) {
			std::memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			std::memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			valid = mat.valid;
		}

		T data[2][2]{ {0, 0}, {0, 0} };
		bool valid = true;

		inline T* operator [] (int index) {
			return data[index];
		}

		inline const T* operator [] (int index) const {
			return data[index];
		}

		//Matrix * Matrix

		inline Matrix2<T> operator * (const Matrix2<T>& mat) {
			return Matrix2<T>({
				{ mat[0][0] * data[0][0] + mat[1][0] * data[0][1], mat[0][1] * data[0][0] + mat[1][1] * data[0][1] },
				{ mat[1][0] * data[1][1] + mat[0][0] * data[1][0], mat[1][1] * data[1][1] + mat[0][1] * data[1][0] },
				});
		}

		inline Matrix2<T> operator / (const Matrix2<T>& mat) {
			return Matrix2<T>({
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][0], data[0][1]), PTOS_ZERO_DIVIDE(mat[0][1], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][1], data[0][1]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[1][1]) + PTOS_ZERO_DIVIDE(mat[0][0], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[1][1]) + PTOS_ZERO_DIVIDE(mat[0][1], data[1][0]) }
				});
		}

		inline Matrix2<T> operator + (const Matrix2<T>& mat) {
			return Matrix2<T>({
				{ data[0][0] + mat[0][0], data[0][1] + mat[0][1] },
				{ data[1][0] + mat[1][0], data[1][1] + mat[1][1] }
				});
		}

		inline Matrix2<T> operator - (const Matrix2<T>& mat) {
			return Matrix2<T>({
				{ data[0][0] - mat[0][0], data[0][1] - mat[0][1] },
				{ data[1][0] - mat[1][0], data[1][1] - mat[1][1] }
				});
		}

		//Matrix * Vector

		inline Vector2<T> operator * (const Vector2<T>& v) {
			return Vector2<T>(
				data[0][0] * v[0] + data[1][0] * v[1],
				data[0][1] * v[0] + data[1][1] * v[1]
			);
		}

		inline Vector2<T> operator / (const Vector2<T>& v) {
			return Vector2<T>(
				PTOS_ZERO_DIVIDE(data[0][0], v[0]) + PTOS_ZERO_DIVIDE(data[1][0], v[1]),
				PTOS_ZERO_DIVIDE(data[0][1], v[0]) + PTOS_ZERO_DIVIDE(data[1][1], v[1])
			);
		}

		// Matrix * T

		inline Matrix2<T> operator * (T m) const {
			return Matrix2<T>({
				{ data[0][0] * m, data[0][1] * m },
				{ data[1][0] * m, data[1][1] * m }
				});
		}

		inline Matrix2<T> operator / (T m) const {
			return Matrix2<T>({
				{ PTOS_ZERO_DIVIDE(data[0][0], m), PTOS_ZERO_DIVIDE(data[0][1], m) },
				{ PTOS_ZERO_DIVIDE(data[1][0], m), PTOS_ZERO_DIVIDE(data[1][1], m) }
				});
		}

		inline Matrix2<T> operator + (T m) const  {
			return Matrix2<T>({
				{ data[0][0] + m, data[0][1] + m },
				{ data[1][0] + m, data[1][1] + m }
				});
		}

		inline Matrix2<T> operator - (T m) const {
			return Matrix2<T>({
				{ data[0][0] - m, data[0][1] - m },
				{ data[1][0] - m, data[1][1] - m }
				});
		}

		inline T determinate() const {
			return data[0][0] * data[1][1] - data[0][1] * data[1][0];
		}

		inline Matrix2<T> inverse() const {
			T data[2][2];
			T det = data[0][0] * data[1][1] - data[0][1] * data[1][0];
			if (det != 0)
				return Matrix2({
					{data[1][1] / det, -data[0][1] / det},
					{-data[1][0] / det, data[0][0] / det}
					});
			Matrix2<T> invalid(data);
			invalid.valid = false;
			return invalid;
		}
	};

	template <typename T> struct Matrix3 {
		static inline Matrix3 identity() {
			return Matrix3({
				{1, 0, 0},
				{0, 1, 0},
				{0, 0, 1}
			});
		}

		Matrix3() {}

		Matrix3(const T(&data)[3][3]) {
			std::memcpy(&this->data, &data, sizeof(T[3][3]));
		}

		Matrix3(const Matrix2<T>& mat) {
			std::memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			std::memcpy(&data[1], &mat.data[1], sizeof(T[2]));
			std::memcpy(&data[2], &mat.data[2], sizeof(T[2]));
			valid = mat.valid
		}

		Matrix3(const Matrix4<T>& mat) {
			std::memcpy(&data[0], &mat.data[0], sizeof(T[3]));
			std::memcpy(&data[1], &mat.data[1], sizeof(T[3]));
			std::memcpy(&data[2], &mat.data[2], sizeof(T[3]));
		}

		T data[3][3]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
		bool valid = true;

		inline const T* operator [] (int index) const {
			return data[index];
		}

		//Matrix * Matrix

		inline Matrix3<T> operator * (const Matrix3<T>& mat) const {
			return Matrix3<T>({
				{ mat[0][0] * data[0][0] + mat[1][0] * data[0][1] + mat[2][0] * data[0][2], mat[0][1] * data[0][0] + mat[1][1] * data[0][1] + mat[2][1] * data[0][2], mat[0][2] * data[0][0] + mat[1][2] * data[0][1] + mat[2][2] * data[0][2] },
				{ mat[1][0] * data[1][1] + mat[2][0] * data[1][2] + mat[0][0] * data[1][0], mat[1][1] * data[1][1] + mat[2][1] * data[1][2] + mat[0][1] * data[1][0], mat[1][2] * data[1][1] + mat[2][2] * data[1][2] + mat[0][2] * data[1][0] },
				{ mat[1][0] * data[2][1] + mat[2][0] * data[2][2] + mat[0][0] * data[2][0], mat[1][1] * data[2][1] + mat[2][1] * data[2][2] + mat[0][1] * data[2][0], mat[1][2] * data[2][1] + mat[2][2] * data[2][2] + mat[0][2] * data[2][0] }
				});
		}

		inline Matrix3<T> operator / (const Matrix3<T>& mat) const {
			return Matrix3<T>({
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][0], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[0][2]), PTOS_ZERO_DIVIDE(mat[0][1], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][1], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[0][2]), PTOS_ZERO_DIVIDE(mat[0][2], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][2], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[0][2]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[1][2]) + PTOS_ZERO_DIVIDE(mat[0][0], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[1][2]) + PTOS_ZERO_DIVIDE(mat[0][1], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[1][2]) + PTOS_ZERO_DIVIDE(mat[0][2], data[1][0]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[2][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][0], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[2][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][1], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[2][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][2], data[2][0]) }
				});
		}

		inline Matrix3<T> operator + (const Matrix3<T>& mat) const {
			return Matrix3<T>({
				{ data[0][0] + mat[0][0], data[0][1] + mat[0][1], data[0][2] + mat[0][2] },
				{ data[1][0] + mat[1][0], data[1][1] + mat[1][1], data[1][2] + mat[1][2] },
				{ data[2][0] + mat[2][0], data[2][1] + mat[2][1], data[2][2] + mat[2][2] }
				});
		}

		inline Matrix3<T> operator - (const Matrix3<T>& mat) const {
			return Matrix3<T>({
				{ data[0][0] - mat[0][0], data[0][1] - mat[0][1], data[0][2] - mat[0][2] },
				{ data[1][0] - mat[1][0], data[1][1] - mat[1][1], data[1][2] - mat[1][2] },
				{ data[2][0] - mat[2][0], data[2][1] - mat[2][1], data[2][2] - mat[2][2] }
				});
		}

		//Matrix * Vector

		inline Vector3<T> operator * (const Vector3<T>& v) const {
			return Vector3<T>(
				data[0][0] * v[0] + data[0][1] * v[1] + data[0][2] * v[2],
				data[1][0] * v[0] + data[1][1] * v[1] + data[1][2] * v[2],
				data[2][0] * v[0] + data[2][1] * v[1] + data[2][2] * v[2]
			);
		}

		inline Vector3<T> operator / (const Vector3<T>& v) const {
			return Vector3<T>(
				PTOS_ZERO_DIVIDE(data[0][0], v[0]) + PTOS_ZERO_DIVIDE(data[0][1], v[1]) + PTOS_ZERO_DIVIDE(data[0][2], v[2]),
				PTOS_ZERO_DIVIDE(data[1][0], v[0]) + PTOS_ZERO_DIVIDE(data[1][1], v[1]) + PTOS_ZERO_DIVIDE(data[1][2], v[2]),
				PTOS_ZERO_DIVIDE(data[2][0], v[0]) + PTOS_ZERO_DIVIDE(data[2][1], v[1]) + PTOS_ZERO_DIVIDE(data[2][2], v[2])
			);
		}

		//Matrix * T

		inline Matrix3<T> operator * (T m) const {
			return Matrix3<T>({
				{ data[0][0] * m, data[0][1] * m, data[0][2] * m },
				{ data[1][0] * m, data[1][1] * m, data[1][2] * m },
				{ data[2][0] * m, data[2][1] * m, data[2][2] * m }

				});
		}

		inline Matrix3<T> operator / (T m) const {
			return Matrix3<T>({
				{ PTOS_ZERO_DIVIDE(data[0][0], m), PTOS_ZERO_DIVIDE(data[0][1], m), PTOS_ZERO_DIVIDE(data[0][2], m) },
				{ PTOS_ZERO_DIVIDE(data[1][0], m), PTOS_ZERO_DIVIDE(data[1][1], m), PTOS_ZERO_DIVIDE(data[1][2], m) },
				{ PTOS_ZERO_DIVIDE(data[2][0], m), PTOS_ZERO_DIVIDE(data[2][1], m), PTOS_ZERO_DIVIDE(data[2][2], m) }

				});
		}

		inline Matrix3<T> operator + (T m) const {
			return Matrix3<T>({
				{ data[0][0] + m, data[0][1] + m, data[0][2] + m },
				{ data[1][0] + m, data[1][1] + m, data[1][2] + m },
				{ data[2][0] + m, data[2][1] + m, data[2][2] + m }

				});
		}

		inline Matrix3<T> operator - (T m) const {
			return Matrix3<T>({
				{ data[0][0] - m, data[0][1] - m, data[0][2] - m },
				{ data[1][0] - m, data[1][1] - m, data[1][2] - m },
				{ data[2][0] - m, data[2][1] - m, data[2][2] - m }
				});
		}

		inline T determinant() const {
			return mat[0][0] * mat[1][1] * mat[2][2] + mat[0][1] * mat[1][2] * mat[2][0] + mat[0][2] * mat[1][0] * mat[2][1] - mat[0][1] * mat[1][0] * mat[2][2] - mat[0][0] * mat[1][2] * mat[2][1] - mat[0][2] * mat[1][1] * mat[2][0];
		}

		//cite: https://www.cuemath.com/algebra/adjoint-of-a-matrix/
		//ignore the sign flipping step
		inline Matrix3<T> inverse() const {
			T det = data.determinant();
			if (det != 0)
				return Matrix3<T>({
					{(data[1][1] * data[2][2] - data[1][2] * data[2][1]) / det, (data[2][1] * data[0][2] - data[2][2] * data[0][1]) / det, (data[0][1] * data[1][2] - data[0][2] * data[1][1]) / det},
					{(data[1][2] * data[2][0] - data[1][0] * data[2][2]) / det, (data[2][2] * data[0][0] - data[2][0] * data[0][2]) / det, (data[0][2] * data[1][0] - data[0][0] * data[1][2]) / det},
					{(data[1][0] * data[2][1] - data[1][1] * data[2][0]) / det, (data[2][0] * data[0][1] - data[2][1] * data[0][0]) / det, (data[0][0] * data[1][1] - data[0][1] * data[1][0]) / det}
					});
			Matrix3<T> invalid(data);
			invalid.valid = false;
			return invalid;
		}
	};

	template <typename T> struct Matrix4 {
		static inline Matrix4 identity() {
			return Matrix4({
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0}
				{0, 0, 0, 1}
			});
		}

		Matrix4() {}

		Matrix4(const T(&data)[4][4]) {
			std::memcpy(&this->data, &data, sizeof(T[4][4]));
		}

		Matrix4(const Matrix2<T>& mat) {
			std::memcpy(&data[0], &mat.data[0], sizeof(T[2]));
			std::memcpy(&data[1], &mat.data[1], sizeof(T[2]));
			valid = mat.valid;
		}

		Matrix4(const Matrix3<T>& mat) {
			std::memcpy(&data[0], &mat.data[0], sizeof(T[3]));
			std::memcpy(&data[1], &mat.data[1], sizeof(T[3]));
			std::memcpy(&data[2], &mat.data[2], sizeof(T[3]));
			valid = mat.valid;
		}

		T data[4][4]{ {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
		bool valid = true;

		inline T* operator [] (int index) {
			return data[index];
		}

		inline const T* operator [] (int index) const {
			return data[index];
		}

		//Matrix * Matrix

		inline Matrix4<T> operator * (const Matrix4<T>& mat) const {
			return Matrix4<T>({
				{ mat[0][0] * data[0][0] + mat[1][0] * data[0][1] + mat[2][0] * data[0][2] + mat[3][0] * data[0][3], mat[0][1] * data[0][0] + mat[1][1] * data[0][1] + mat[2][1] * data[0][2] + mat[3][1] * data[0][3], mat[0][2] * data[0][0] + mat[1][2] * data[0][1] + mat[2][2] * data[0][2] + mat[3][2] * data[0][3], mat[0][3] * data[0][0] + mat[1][3] * data[0][1] + mat[2][3] * data[0][2] + mat[3][3] * data[0][3] },
				{ mat[1][0] * data[1][1] + mat[2][0] * data[1][2] + mat[3][0] * data[1][3] + mat[0][0] * data[1][0], mat[1][1] * data[1][1] + mat[2][1] * data[1][2] + mat[3][1] * data[1][3] + mat[0][1] * data[1][0], mat[1][2] * data[1][1] + mat[2][2] * data[1][2] + mat[3][2] * data[1][3] + mat[0][2] * data[1][0], mat[1][3] * data[1][1] + mat[2][3] * data[1][2] + mat[3][3] * data[1][3] + mat[0][3] * data[1][0] },
				{ mat[1][0] * data[2][1] + mat[3][0] * data[2][3] + mat[2][0] * data[2][2] + mat[0][0] * data[2][0], mat[1][1] * data[2][1] + mat[3][1] * data[2][3] + mat[2][1] * data[2][2] + mat[0][1] * data[2][0], mat[1][2] * data[2][1] + mat[3][2] * data[2][3] + mat[2][2] * data[2][2] + mat[0][2] * data[2][0], mat[1][3] * data[2][1] + mat[3][3] * data[2][3] + mat[2][3] * data[2][2] + mat[0][3] * data[2][0] },
				{ mat[0][0] * data[3][0] + mat[2][0] * data[3][2] + mat[3][0] * data[3][3] + mat[1][0] * data[3][1], mat[0][1] * data[3][0] + mat[2][1] * data[3][2] + mat[3][1] * data[3][3] + mat[1][1] * data[3][1], mat[0][2] * data[3][0] + mat[2][2] * data[3][2] + mat[3][2] * data[3][3] + mat[1][2] * data[3][1], mat[0][3] * data[3][0] + mat[2][3] * data[3][2] + mat[3][3] * data[3][3] + mat[1][3] * data[3][1] }
				});
		}

		inline Matrix4<T> operator / (const Matrix4<T>& mat) const {
			return Matrix4<T>({
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][0], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][0], data[0][3]), PTOS_ZERO_DIVIDE(mat[0][1], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][1], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][1], data[0][3]), PTOS_ZERO_DIVIDE(mat[0][2], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][2], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][2], data[0][3]), PTOS_ZERO_DIVIDE(mat[0][3], data[0][0]) + PTOS_ZERO_DIVIDE(mat[1][3], data[0][1]) + PTOS_ZERO_DIVIDE(mat[2][3], data[0][2]) + PTOS_ZERO_DIVIDE(mat[3][3], data[0][3]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][0], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][0], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][0], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][1], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][1], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][1], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][2], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][2], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][2], data[1][0]), PTOS_ZERO_DIVIDE(mat[1][3], data[1][1]) + PTOS_ZERO_DIVIDE(mat[2][3], data[1][2]) + PTOS_ZERO_DIVIDE(mat[3][3], data[1][3]) + PTOS_ZERO_DIVIDE(mat[0][3], data[1][0]) },
				{ PTOS_ZERO_DIVIDE(mat[1][0], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][0], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][0], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][0], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][1], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][1], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][1], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][1], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][2], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][2], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][2], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][2], data[2][0]), PTOS_ZERO_DIVIDE(mat[1][3], data[2][1]) + PTOS_ZERO_DIVIDE(mat[3][3], data[2][3]) + PTOS_ZERO_DIVIDE(mat[2][3], data[2][2]) + PTOS_ZERO_DIVIDE(mat[0][3], data[2][0]) },
				{ PTOS_ZERO_DIVIDE(mat[0][0], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][0], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][0], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][0], data[3][1]), PTOS_ZERO_DIVIDE(mat[0][1], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][1], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][1], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][1], data[3][1]), PTOS_ZERO_DIVIDE(mat[0][2], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][2], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][2], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][2], data[3][1]), PTOS_ZERO_DIVIDE(mat[0][3], data[3][0]) + PTOS_ZERO_DIVIDE(mat[2][3], data[3][2]) + PTOS_ZERO_DIVIDE(mat[3][3], data[3][3]) + PTOS_ZERO_DIVIDE(mat[1][3], data[3][1]) }
				});
		}

		inline Matrix4<T> operator + (const Matrix4<T>& mat) const {
			return Matrix4<T>({
				{ data[0][0] + mat[0][0], data[0][1] + mat[0][1], data[0][2] + mat[0][2], data[0][3] + mat[0][3] },
				{ data[1][0] + mat[1][0], data[1][1] + mat[1][1], data[1][2] + mat[1][2], data[1][3] + mat[1][3] },
				{ data[2][0] + mat[2][0], data[2][1] + mat[2][1], data[2][2] + mat[2][2], data[2][3] + mat[2][3] },
				{ data[3][0] + mat[3][0], data[3][1] + mat[3][1], data[3][2] + mat[3][2], data[3][3] + mat[3][3] },
				});
		}

		inline Matrix4<T> operator - (const Matrix4<T>& mat) const {
			return Matrix4<T>({
				{ data[0][0] - mat[0][0], data[0][1] - mat[0][1], data[0][2] - mat[0][2], data[0][3] - mat[0][3] },
				{ data[1][0] - mat[1][0], data[1][1] - mat[1][1], data[1][2] - mat[1][2], data[1][3] - mat[1][3] },
				{ data[2][0] - mat[2][0], data[2][1] - mat[2][1], data[2][2] - mat[2][2], data[2][3] - mat[2][3] },
				{ data[3][0] - mat[3][0], data[3][1] - mat[3][1], data[3][2] - mat[3][2], data[3][3] - mat[3][3] },
				});
		}

		//Matrix * Vector

		inline Vector4<T> operator * (const Vector4<T>& v) const {
			return Vector4<T>(
				data[0][0] * v[0] + data[0][1] * v[1] + data[0][2] * v[2] + data[0][3] * v[3],
				data[1][0] * v[0] + data[1][1] * v[1] + data[1][2] * v[2] + data[1][3] * v[3],
				data[2][0] * v[0] + data[2][1] * v[1] + data[2][2] * v[2] + data[2][3] * v[3],
				data[3][0] * v[0] + data[3][1] * v[1] + data[3][2] * v[2] + data[3][3] * v[3]
			);
		}

		inline Vector4<T> operator / (const Vector4<T>& v) const {
			return Vector4<T>(
				PTOS_ZERO_DIVIDE(data[0][0], v[0]) + PTOS_ZERO_DIVIDE(data[0][1], v[1]) + PTOS_ZERO_DIVIDE(data[0][2], v[2]) + PTOS_ZERO_DIVIDE(data[0][3], v[3]),
				PTOS_ZERO_DIVIDE(data[1][0], v[0]) + PTOS_ZERO_DIVIDE(data[1][1], v[1]) + PTOS_ZERO_DIVIDE(data[1][2], v[2]) + PTOS_ZERO_DIVIDE(data[1][3], v[3]),
				PTOS_ZERO_DIVIDE(data[2][0], v[0]) + PTOS_ZERO_DIVIDE(data[2][1], v[1]) + PTOS_ZERO_DIVIDE(data[2][2], v[2]) + PTOS_ZERO_DIVIDE(data[2][3], v[3]),
				PTOS_ZERO_DIVIDE(data[3][0], v[0]) + PTOS_ZERO_DIVIDE(data[3][1], v[1]) + PTOS_ZERO_DIVIDE(data[3][2], v[2]) + PTOS_ZERO_DIVIDE(data[3][3], v[3])
			);
		}

		//Matrix * T

		inline Matrix4<T> operator * (T m) const {
			return Matrix4<T>({
				{ data[0][0] * m, data[0][1] * m, data[0][2] * m, data[0][3] * m },
				{ data[1][0] * m, data[1][1] * m, data[1][2] * m, data[1][3] * m },
				{ data[2][0] * m, data[2][1] * m, data[2][2] * m, data[2][3] * m },
				{ data[3][0] * m, data[3][1] * m, data[3][2] * m, data[3][3] * m }
				});
		}

		inline Matrix4<T> operator / (T m) const {
			return Matrix4<T>({
				{ PTOS_ZERO_DIVIDE(data[0][0], m), PTOS_ZERO_DIVIDE(data[0][1], m), PTOS_ZERO_DIVIDE(data[0][2], m), PTOS_ZERO_DIVIDE(data[0][3], m) },
				{ PTOS_ZERO_DIVIDE(data[1][0], m), PTOS_ZERO_DIVIDE(data[1][1], m), PTOS_ZERO_DIVIDE(data[1][2], m), PTOS_ZERO_DIVIDE(data[1][3], m) },
				{ PTOS_ZERO_DIVIDE(data[2][0], m), PTOS_ZERO_DIVIDE(data[2][1], m), PTOS_ZERO_DIVIDE(data[2][2], m), PTOS_ZERO_DIVIDE(data[2][3], m) },
				{ PTOS_ZERO_DIVIDE(data[3][0], m), PTOS_ZERO_DIVIDE(data[3][1], m), PTOS_ZERO_DIVIDE(data[3][2], m), PTOS_ZERO_DIVIDE(data[3][3], m) }
				});
		}

		inline Matrix4<T> operator + (T m) const {
			return Matrix4<T>({
				{ data[0][0] + m, data[0][1] + m, data[0][2] + m, data[0][3] + m },
				{ data[1][0] + m, data[1][1] + m, data[1][2] + m, data[1][3] + m },
				{ data[2][0] + m, data[2][1] + m, data[2][2] + m, data[2][3] + m },
				{ data[3][0] + m, data[3][1] + m, data[3][2] + m, data[3][3] + m }
				});
		}

		inline Matrix4<T> operator - (T m) const {
			return Matrix4<T>({
				{ data[0][0] - m, data[0][1] - m, data[0][2] - m, data[0][3] - m },
				{ data[1][0] - m, data[1][1] - m, data[1][2] - m, data[1][3] - m },
				{ data[2][0] - m, data[2][1] - m, data[2][2] - m, data[2][3] - m },
				{ data[3][0] - m, data[3][1] - m, data[3][2] - m, data[3][3] - m }
				});
		}

		inline T determinate() const {
			return data[0][0] * data[1][1] * data[2][2] * data[3][3] + data[1][3] * data[2][1] * data[3][2] + data[1][2] * data[2][3] * data[3][1] - data[1][2] * data[2][1] * data[3][3] - data[1][1] * data[2][3] * data[3][2] - data[1][3] * data[2][2] * data[3][1]
				+ data[1][0] * data[0][3] * data[2][2] * data[3][1] + data[0][2] * data[2][1] * data[3][3] + data[0][1] * data[2][3] * data[3][2] - data[0][3] * data[2][1] * data[3][2] - data[0][2] * data[2][3] * data[3][1] - data[0][1] * data[2][2] * data[3][3]
				+ data[2][0] * data[0][2] * data[1][3] * data[3][1] + data[0][1] * data[1][2] * data[3][3] + data[0][3] * data[1][1] * data[3][2] - data[0][1] * data[1][3] * data[3][2] - data[0][3] * data[1][2] * data[3][1] - data[0][2] * data[1][1] * data[3][3]
				+ data[3][0] * data[0][2] * data[1][1] * data[2][3] + data[0][1] * data[1][3] * data[2][2] + data[0][3] * data[1][2] * data[2][1] - data[0][1] * data[1][2] * data[2][3] - data[0][3] * data[1][1] * data[2][2] - data[0][2] * data[1][3] * data[2][1];
		}

		//cite: https://www.youtube.com/shorts/b3AOCABQTjA
		Matrix4<T> inverse() const {
			T c0 = data[1][1] * data[2][2] * data[3][3] + data[1][3] * data[2][1] * data[3][2] + data[1][2] * data[2][3] * data[3][1] - data[1][2] * data[2][1] * data[3][3] - data[1][1] * data[2][3] * data[3][2] - data[1][3] * data[2][2] * data[3][1];
			T c1 = data[0][3] * data[2][2] * data[3][1] + data[0][2] * data[2][1] * data[3][3] + data[0][1] * data[2][3] * data[3][2] - data[0][3] * data[2][1] * data[3][2] - data[0][2] * data[2][3] * data[3][1] - data[0][1] * data[2][2] * data[3][3];
			T c2 = data[0][2] * data[1][3] * data[3][1] + data[0][1] * data[1][2] * data[3][3] + data[0][3] * data[1][1] * data[3][2] - data[0][1] * data[1][3] * data[3][2] - data[0][3] * data[1][2] * data[3][1] - data[0][2] * data[1][1] * data[3][3];
			T c3 = data[0][2] * data[1][1] * data[2][3] + data[0][1] * data[1][3] * data[2][2] + data[0][3] * data[1][2] * data[2][1] - data[0][1] * data[1][2] * data[2][3] - data[0][3] * data[1][1] * data[2][2] - data[0][2] * data[1][3] * data[2][1];

			T det = data[0][0] * c0 + data[1][0] * c1 + data[2][0] * c2 + data[3][0] * c3;
			if (det != 0)
				return Matrix4<T>({
					{ c0 / det, c1 / det, c2 / det, c3 / det },
					{ (data[1][3] * data[2][2] * data[3][0] + data[1][2] * data[2][0] * data[3][3] + data[1][0] * data[2][3] * data[3][2] - data[1][2] * data[2][3] * data[3][0] - data[1][0] * data[2][2] * data[3][3] - data[1][3] * data[2][0] * data[3][2]) / det, (data[0][0] * data[2][2] * data[3][3] + data[0][3] * data[2][0] * data[3][2] + data[0][2] * data[2][3] * data[3][0] - data[0][0] * data[2][3] * data[3][2] - data[0][3] * data[2][2] * data[3][0] - data[0][2] * data[2][0] * data[3][3]) / det, (data[0][2] * data[1][0] * data[3][3] + data[0][0] * data[1][3] * data[3][2] + data[0][3] * data[1][2] * data[3][0] - data[0][3] * data[1][0] * data[3][2] - data[0][2] * data[1][3] * data[3][0] - data[0][0] * data[1][2] * data[3][3]) / det, (data[0][2] * data[1][3] * data[2][0] + data[0][0] * data[1][2] * data[2][3] + data[0][3] * data[1][0] * data[2][2] - data[0][3] * data[1][2] * data[2][0] - data[0][2] * data[1][0] * data[2][3] - data[0][0] * data[1][3] * data[2][2]) / det },
					{ (data[1][3] * data[2][0] * data[3][1] + data[1][1] * data[2][3] * data[3][0] + data[1][0] * data[2][1] * data[3][3] - data[1][0] * data[2][3] * data[3][1] - data[1][3] * data[2][1] * data[3][0] - data[1][1] * data[2][0] * data[3][3]) / det, (data[0][1] * data[2][0] * data[3][3] + data[0][0] * data[2][3] * data[3][1] + data[0][3] * data[2][1] * data[3][0] - data[0][1] * data[2][3] * data[3][0] - data[0][0] * data[2][1] * data[3][3] - data[0][3] * data[2][0] * data[3][1]) / det, (data[0][0] * data[1][1] * data[3][3] + data[0][3] * data[1][0] * data[3][1] + data[0][1] * data[1][3] * data[3][0] - data[0][3] * data[1][1] * data[3][0] - data[0][1] * data[1][0] * data[3][3] - data[0][0] * data[1][3] * data[3][1]) / det, (data[0][0] * data[1][3] * data[2][1] + data[0][3] * data[1][1] * data[2][0] + data[0][1] * data[1][0] * data[2][3] - data[0][3] * data[1][0] * data[2][1] - data[0][1] * data[1][3] * data[2][0] - data[0][0] * data[1][1] * data[2][3]) / det },
					{ (data[1][1] * data[2][0] * data[3][2] + data[1][0] * data[2][2] * data[3][1] + data[1][2] * data[2][1] * data[3][0] - data[1][0] * data[2][1] * data[3][2] - data[1][2] * data[2][0] * data[3][1] - data[1][1] * data[2][2] * data[3][0]) / det, (data[0][2] * data[2][0] * data[3][1] + data[0][1] * data[2][2] * data[3][0] + data[0][0] * data[2][1] * data[3][2] - data[0][2] * data[2][1] * data[3][0] - data[0][1] * data[2][0] * data[3][2] - data[0][0] * data[2][2] * data[3][1]) / det, (data[0][0] * data[1][2] * data[3][1] + data[0][2] * data[1][1] * data[3][0] + data[0][1] * data[1][0] * data[3][2] - data[0][1] * data[1][2] * data[3][0] - data[0][0] * data[1][1] * data[3][2] - data[0][2] * data[1][0] * data[3][1]) / det, (data[0][0] * data[1][1] * data[2][2] + data[0][2] * data[1][0] * data[2][1] + data[0][1] * data[1][2] * data[2][0] - data[0][1] * data[1][0] * data[2][2] - data[0][0] * data[1][2] * data[2][1] - data[0][2] * data[1][1] * data[2][0]) / det }
					});
			Matrix4<T> invalid(data);
			invalid.valid = false;
			return invalid;
		}
	};

	template<typename From, typename To> Matrix2<To> mat_recast(const Matrix2<From>& from) {
		return Matrix2<To>({
			{(To)from[0][0], (To)from[0][1]},
			{(To)from[1][1], (To)from[1][1]}
			});
	}

	template<typename From, typename To> Matrix3<To> mat_recast(const Matrix3<From>& from) {
		return Matrix3<To>({
			{(To)from[0][0], (To)from[0][1], (To)from[0][2] },
			{(To)from[1][0], (To)from[1][1], (To)from[1][2] },
			{(To)from[2][0], (To)from[2][1], (To)from[2][2] },
			});
	}

	template<typename From, typename To> Matrix4<To> mat_recast(const Matrix4<From>& from) {
		return Matrix4<To>({
			{(To)from[0][0], (To)from[0][1], (To)from[0][2], (To)from[0][3] },
			{(To)from[1][0], (To)from[1][1], (To)from[1][2], (To)from[1][3] },
			{(To)from[2][0], (To)from[2][1], (To)from[2][2], (To)from[2][3] },
			{(To)from[3][0], (To)from[3][1], (To)from[3][2], (To)from[3][3] }
			});
	}
}