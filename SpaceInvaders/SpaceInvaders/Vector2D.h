#ifndef MATH_VECTOR_2D_H
#define MATH_VECTOR_2D_H

#include "Point.h"
#include <ostream>

namespace math
{
	struct Vector2D
	{
		Point origin{ 0, 0 };
		float x = 0;
		float y = 0;

		Vector2D(const Point origin, const float x, const float y)
			: origin(origin), x(x), y(y) {};

		Vector2D& operator+=(const Vector2D &other)
		{
			this->x += other.x;
			this->y += other.y;

			return *this;
		}

		Vector2D& operator-=(const Vector2D &other)
		{
			this->x -= other.x;
			this->y -= other.y;

			return *this;
		}

		Vector2D& operator*=(const Vector2D &other)
		{
			this->x *= other.x;
			this->y *= other.y;

			return *this;
		}

		Vector2D& operator*=(const float scalar)
		{
			this->x = x * scalar;
			this->y = y * scalar;

			return *this;
		}


	};

	inline std::ostream& operator << (std::ostream &stream, Vector2D &vector) 
	{
		return stream << "Vector -> (X: " << vector.x << ", Y: " << vector.y << ")";
	}
}

#endif