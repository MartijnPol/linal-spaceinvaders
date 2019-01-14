#ifndef MATH_VECTOR_3D_H
#define MATH_VECTOR_3D_H

#include "Point.h"

namespace math
{
	template<typename T>
	struct Vector3D
	{
		Point origin{ 0, 0 };
		T x, y, z;

		Vector3D(const Point origin, const T x, const T y, const T z)
			: origin(origin), x(x), y(y), z(z) {}

		Vector3D<T>& operator+=(const Vector3D<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;

			return *this;
		}

		Vector3D<T>& operator-=(const Vector3D<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;

			return *this;
		}

		Vector3D<T>& operator*=(const float scalar)
		{
			this->x = this->x * scalar;
			this->y = this->y * scalar;
			this->z = this->z * scalar;

			return *this;
		}

		float inner_product(const Vector3D<T> &other) const
		{
			return (x * other.x) + (y * other.y) + (z * other.z);
		}

		float angle(const Vector3D<T> &other) const
		{
			return std::acos(inner_product(other) / (length() * other.length()));
		}

		float length() const
		{
			return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
		}

		Vector3D<T> cross_product(const Vector3D<T> &other) const
		{
			auto cross_vector = Vector3D<T>({ origin.x, origin.y }, 0, 0, 0);

			cross_vector.x = (y * other.z - z * other.y);
			cross_vector.y = (z * other.x - x * other.z);
			cross_vector.z = (x * other.y - y * other.x);

			return cross_vector;
		}
	};

	template <typename T>
	std::ostream& operator << (std::ostream &stream, const Vector3D<T> &vector)
	{
		return stream << "Vector -> (X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z << ")";
	}
}

#endif