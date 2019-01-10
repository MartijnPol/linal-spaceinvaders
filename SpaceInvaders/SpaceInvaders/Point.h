#ifndef MATH_POINT_H
#define MATH_POINT_H

#include <ostream>

namespace math
{
	struct Point
	{
		float x, y;

		Point(float x, float y);
		Point& add(const Point &other);
	};
}

#endif