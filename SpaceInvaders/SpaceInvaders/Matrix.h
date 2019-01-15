#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "Math.h"
#include <utility>
#include <vector>
#include <cassert>
#include "Vector3D.h"
#include "Line3D.h"

namespace math
{
	template<typename T> struct Matrix
	{
		int rows{ 0 }, columns{ 0 };
		std::vector<T> inner;

		Matrix() = default;

		Matrix(const int rows, const int columns)
			: rows(rows), columns(columns), inner(rows * columns) {}

		Matrix(const int rows, const int columns, std::vector<T> values)
			: rows(rows), columns(columns), inner(std::move(values)) {}

		T operator() (const int row, const int column) {
			return inner[row * columns + column];
		}

		T const &operator() (const int row, const int column) const {
			return inner[row * columns + column];
		}

		T min(const int row)
		{
			auto min = std::numeric_limits<T>::max();
			for (auto i = 0; i < columns; ++i)
			{
				const auto x = at(row, i);
				if (x < min)
				{
					min = x;
				}
			}

			return min;
		}

		T max(int const row)
		{
			auto max = 0.0f;
			for (auto i = 0; i < columns; ++i)
			{
				const auto x = at(row, i);
				if (x > max)
				{
					max = x;
				}
			}

			return max;
		}

		Vector3D<T> get_middle_vector()
		{
			const auto middle_x = (max(0) + min(0)) / 2;
			const auto middle_y = (max(1) + min(1)) / 2;
			const auto middle_z = (max(2) + min(2)) / 2;

			return Vector3D<T>{middle_x, middle_y, middle_z};
		}

		Vector3D<T> get_point_vector(const int index)
		{
			const auto x = at(0, index);
			const auto y = at(1, index);
			const auto z = at(2, index);

			return Vector3D<T>{x, y, z};
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

	template<class T>
	Vector3D<T> operator * (const Matrix<T>& left, const Vector3D<T> right)
	{
		Vector3D<T> result{};
		for (auto row_index = 0; row_index < left.rows; row_index++)
		{
			for (auto column_index = 0; column_index < left.rows; column_index++)
			{
				if (row_index == 0)
				{
					result.x += left(row_index, column_index) * right.x;
				}
				else if (row_index == 1)
				{
					result.y += left(row_index, column_index) * right.y;
				}
				else if (row_index == 2)
				{
					result.z += left(row_index, column_index) * right.z;
				}
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
	Matrix<T> translate(Matrix<T> &matrix, T x, T y)
	{
		auto translation_matrix = translate(x, y);

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
	Matrix<T> scale(Vector3D<T> &vector)
	{
		return Matrix<T>(4, 4, { vector.x, 0, 0, 0,
								 0, vector.y, 0, 0,
								 0, 0, vector.z, 0,
								 0, 0, 0, 1 });
	}

	template<class T>
	Matrix<T> scale(Matrix<T> &matrix, Vector3D<T> &vector)
	{
		auto scale_matrix = scale(vector);

		translate(matrix, -vector.x, -vector.y, -vector.z);

		scale_matrix = scale_matrix * matrix;

		translate(matrix, vector.x, vector.y, vector.z);

		return scale_matrix;
	}

	template<class T>
	Matrix<T> translate(Vector3D<T> vector) {
		return Matrix<T>(4, 4, { 1, 0, 0, vector.x,
								 0, 1, 0, vector.y,
								 0, 0, 1, vector.z,
								 0, 0, 0, 1 });
	}

	template<class T>
	Matrix<T> translate(Matrix<T> &matrix, T x, T y, T z)
	{
		auto translation_vector = Vector3D<T>{ x, y, z };
		return translate(matrix, translation_vector);
	}

	template<class T>
	Matrix<T> translate(Matrix<T> &matrix, Vector3D<T> vector)
	{
		Matrix<T> translated_matrix = translate(vector);

		translated_matrix = translated_matrix * matrix;

		return translated_matrix;
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
	Matrix<T> rotate(Matrix<T>& matrix, Line3D line, T degrees)
	{
		const auto t1 = std::atan2(line.z(), line.x());
		const auto t2 = std::acosf(std::sqrtf(pow(line.x(), 2) + pow(line.z(), 2)) / line.length());

		const auto to_origin = translate(line.start);
		const auto from_origin = translate(Vector3D<float>{-line.start});

		const auto m1 = rotate_y(t1);
		const auto m2 = rotate_z(t2);
		const auto m3 = rotate_x(degrees);
		const auto m4 = rotate_z(-t2);
		const auto m5 = rotate_y(-t1);

		auto step_one = from_origin * matrix;

		auto step_two = m1 * step_one;
		auto step_three = m2 * step_two;
		auto step_four = m3 * step_three;
		auto step_five = m4 * step_four;
		auto step_six = m5 * step_five;

		auto step_seven = to_origin * step_six;

		return step_seven;
	}

	template<class T>
	Matrix<T> rotate(Line3D line, T degrees)
	{
		const auto t1 = std::atan2(line.z(), line.x());
		const auto t2 = std::acosf(std::sqrtf(pow(line.x(), 2) + pow(line.z(), 2)) / line.length());

		const auto m1 = rotate_y(t1);
		const auto m2 = rotate_z(t2);
		const auto m3 = rotate_x(degrees);
		const auto m4 = rotate_z(-t2);
		const auto m5 = rotate_y(-t1);

		auto step_one = m2 * m1;
		auto step_two = m3 * step_one;
		auto step_three = m4 * step_two;
		auto step_four = m5 * step_three;

		return step_four;
		
	}

	template<class T>
	Matrix<T> rotate(Vector3D<T> vector)
	{
		return rotate_z(vector.z) * rotate_y(vector.y) * rotate_x(vector.x);
	}

	template<class T>
	Matrix<T> rotate(Matrix<T> &matrix, Vector3D<T> vector)
	{
		auto result = rotate(vector);

		result = result * matrix;

		return result;
	}

#pragma endregion

	template<class T>
	bool operator==(const Matrix<T>& left, const Matrix<T>& right)
	{
		if (left.columns != right.columns || left.rows != right.rows)
			return false;

		for (size_t y = 0; y < right.rows; y++)
		{
			for (size_t x = 0; x < right.columns; x++)
			{
				if (left(y, x) != right(y, x))
					return false;
			}
		}

		return true;
	}
}

#endif