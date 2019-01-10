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
	};

	inline std::ostream& operator << (std::ostream &stream, const Vector3D &vector) 
	{
		return stream << "Vector -> (X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z << ")";
	}
}

#endif