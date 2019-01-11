#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "Math.h"
#include <utility>
#include <vector>
#include <cassert>
#include <iostream>
#include "Vector3D.h"

namespace math
{
	template<typename T> struct Matrix
	{
		int rows, columns;
		std::vector<T> inner;

		Matrix(const int rows, const int columns)
			: rows(rows), columns(columns), inner(rows * columns) {}

		Matrix(const int rows, const int columns, std::vector<T> values)
			: rows(rows), columns(columns), inner(std::move(values)) {}

		T operator() (int rows, int columns) {
			return inner[rows * this->columns + columns];
		}

		T const &operator() (int rows, int columns) const {
			return inner[rows * this->columns + columns];
		}

		float at(const int row, const int column) { return inner[row * columns + column]; }
		float at(const int row, const int column) const { return inner[row * columns + column]; }
		void set(const int row, const int column, const float value) { inner[row * columns + column] = value; }

#pragma region Class Operator Overloading

		Matrix<T>& operator+=(const Matrix<T>& other)
		{
			assert(rows == other.rows && columns == other.columns);
			for (auto row = 0; row < rows; row++)
			{
				for (auto column = 0; column < columns; column++)
				{
					at(row, column) += other(row, column);
				}
			}
			return *this;
		}

		Matrix<T>& operator-=(const Matrix<T> &other)
		{
			assert(rows == other.rows && columns == other.columns);
			for (auto row = 0; row < rows; row++)
			{
				for (auto column = 0; column < columns; column++)
				{
					at(row, column) -= other(row, column);
				}
			}
			return *this;
		}

		Matrix<T>& operator*=(const float scalar)
		{
			for (auto row = 0; row < rows; row++)
			{
				for (auto column = 0; column < columns; column++)
				{
					inner[at(row, column)] *= scalar;
				}
			}
			return *this;
		}

		~Matrix() = default;
	};

#pragma endregion

#pragma region Operator overloading

	template<class T>
	Matrix<T> operator * (const T& left, const Matrix<T>& right) {
		Matrix<T> result(right.rows, right.columns);
		for (size_t ri = 0; ri < result.rows; ri++) {
			for (size_t ci = 0; ci < result.columns; ci++) {
				result(ri, ci) = left * right(ri, ci);
			}
		}
		return result;
	}

	template<class T>
	Matrix<T> operator * (const Matrix<T>& left, const T& right) {
		Matrix<T> result(left.rows, left.columns);
		for (size_t ri = 0; ri < result.rows; ri++) {
			for (size_t ci = 0; ci < result.columns; ci++) {
				result(ri, ci) = left(ri, ci) * right;
			}
		}
		return result;
	}

	template<class T>
	Matrix<T> operator * (const Matrix<T>& left, const Matrix<T>& right)
	{
		Matrix<T> result(left.rows, right.columns);

		for (auto row = 0; row < result.rows; row++)
		{
			for (auto column = 0; column < result.columns; column++)
			{
				auto sum = 0.0f;
				for (auto left_column = 0; left_column < left.columns; left_column++)
				{
					sum += left(row, left_column) * right(left_column, column);
				}

				result.set(row, column, sum);
			}
		}

		return result;
	}
#pragma endregion

#pragma region Rotations in 2D
	template<class T>
	Matrix<T> scale(Matrix<T> &matrix, T scale_x, T scale_y)
	{
		auto scale_matrix = Matrix<T>(3, 3, { scale_x, 0, 0,
											  0, scale_y, 0,
											  0, 0, 1 });

		return scale_matrix * matrix;
	}

	template<class T>
	Matrix<T> translate(Matrix<T> &matrix, T translate_x, T translate_y)
	{
		auto translation_matrix = Matrix<T>(3, 3, { 1, 0, translate_x,
													0, 1, translate_y,
													0, 0, 1 });

		return translation_matrix * matrix;
	}

	template<class T>
	Matrix<T> translate(T tx, T ty) {
		return Matrix<T>(3, 3, { 1, 0, tx,
								 0, 1, ty,
								 0, 0, 1 });
	}

	template<class T>
	Matrix<T> rotate(Matrix<T> &matrix, T degrees)
	{
		const auto radian = Math::degrees_to_radius(degrees);
		auto rotation_matrix = Matrix<T>(3, 3, { cos(radian), -sin(radian), 0,
												 sin(radian), cos(radian), 0,
												 0, 0, 1 });

		return rotation_matrix * matrix;
	}


	template<class T>
	Matrix<T> rotate(Matrix<T> &matrix, T degrees, T x, T y)
	{
		const auto radian = Math::degrees_to_radius(degrees);
		translate(matrix, -x, -y);
		auto rotation_matrix = Matrix<T>(3, 3, { cos(radian), -sin(radian), 0,
												 sin(radian), cos(radian), 0,
												 0, 0, 1 });

		matrix = rotation_matrix * matrix;
		translate(matrix, x, y);

		return matrix;
	}
#pragma endregion

#pragma region Rotations in 3D
	template<class T>
	Matrix<T> scale(Matrix<T> &matrix, Vector3D<T> &vector)
	{
		auto scale_matrix = Matrix<T>(4, 4, { vector.x, 0, 0, 0,
											  0, vector.y, 0, 0,
											  0, 0, vector.z, 0,
											  0, 0, 0, 1 });

		return scale_matrix * matrix;
	}

	template<class T>
	Matrix<T> translate(Matrix<T> &matrix, T x, T y, T z)
	{
		auto translation_matrix = Matrix<T>(4, 4, { 1, 0, 0, x,
													0, 1, 0, y,
													0, 0, 1, z,
													0, 0, 0, 1 });

		return translation_matrix * matrix;
	}

	template<class T>
	Matrix<T> translate(Matrix<T> &matrix, Vector3D<T> &vector)
	{
		auto translation_matrix = Matrix<T>(4, 4, { 1, 0, 0, vector.x,
													0, 1, 0, vector.y,
													0, 0, 1, vector.z,
													0, 0, 0, 1 });

		return translation_matrix * matrix;
	}

	template<class T>
	Matrix<T> translate(Vector3D<T> &vector) {
		return Matrix<T>(4, 4, { 1, 0, 0, vector.x,
								 0, 1, 0, vector.y,
								 0, 0, 1, vector.z,
								 0, 0, 0, 1 });
	}

	template<class T>
	Matrix<T> rotate_x(T radian)
	{
		return Matrix<T>(4, 4, { 1, 0, 0, 0,
								 0, cos(radian), -sin(radian), 0,
								 0, sin(radian), cos(radian), 0,
								 0, 0, 0, 1 });


	}

	template<class T>
	Matrix<T> rotate_y(T radian)
	{
		return Matrix<T>(4, 4, { cos(radian), 0, sin(radian), 0,
								 0, 1, 0, 0,
								 -sin(radian), 0, cos(radian), 0,
								 0, 0, 0, 1 });

	}

	template<class T>
	Matrix<T> rotate_z(T radian)
	{
		return Matrix<T>(4, 4, { cos(radian), -sin(radian), 0, 0,
								 sin(radian), cos(radian), 0, 0,
								 0, 0, 1, 0,
								 0, 0, 0, 1 });
	}

	template<class T>
	Matrix<T> rotate(Vector3D<T> vector) {
		auto x_radius = Math::degrees_to_radius(vector.x);
		auto y_radius = Math::degrees_to_radius(vector.y);
		auto z_radius = Math::degrees_to_radius(vector.z);

		auto x_rotation_matrix = rotate_x(x_radius);
		auto y_rotation_matrix = rotate_y(y_radius);
		auto z_rotation_matrix = rotate_z(z_radius);

		return z_rotation_matrix * y_rotation_matrix * x_rotation_matrix;
	}

	template<class T>
	Matrix<T> rotate(Matrix<T> &matrix, Vector3D<T> vector)
	{
		auto result = rotate(vector);

		result = result * matrix;

		return result;
	}

	template<class T>
	bool operator==(const T& left, const T& right)
	{
		return left.inner == right.inner;
	}

#pragma endregion

	template<class T>
	std::ostream& operator << (std::ostream &stream, Matrix<T> &matrix)
	{
		return stream << "Matrix -> " << matrix.columns << "\n";
	}
}

#endif