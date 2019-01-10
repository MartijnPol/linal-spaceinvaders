#ifndef MATH_VECTOR_3D_H
#define MATH_VECTOR_3D_H

#include "Point.h"

namespace math
{
	struct Vector3D
	{
		Point origin{ 0, 0 };
		float x, y, z;

		Vector3D(const Point origin, const float x, const float y, const float z)
			: origin(origin), x(x), y(y), z(z) {}

		Vector3D& operator+=(const Vector3D& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;

			return *this;
		}

		Vector3D& operator-=(const Vector3D& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;

			return *this;
		}

		Vector3D& operator*=(const float scalar)
		{
			this->x = this->x * scalar;
			this->y = this->y * scalar;
			this->z = this->z * scalar;

			return *this;
		}

		float inner_product(const Vector3D &other) const
		{
			return (x * other.x) + (y * other.y) + (z * other.z);
		}

		float angle(const Vector3D &other) const
		{
			return std::acos(inner_product(other) / (length() * other.length()));
		}

		float length() const
		{
			return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
		}

		Vector3D cross_product(const Vector3D &other) const
		{
			auto cross_vector = Vector3D({ origin.x, origin.y }, 0, 0, 0);

			cross_vector.x = (y * other.z - z * other.y);
			cross_vector.y = (z * other.x - x * other.z);
			cross_vector.z = (x * other.y - y * other.x);

			return cross_vector;
		}
	};

	inline std::ostream& operator << (std::ostream &stream, const Vector3D &vector)
	{
		return stream << "Vector -> (X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z << ")";
	}
}

#endif