#include "Point.h"

namespace math
{
	Point::Point(const float x, const float y)
	{
		this->x = x;
		this->y = y;
	}

	Point& Point::add(const Point& other)
	{
		this->x += other.x;
		this->y -= other.y;
		return *this;
	}

	std::ostream& operator<< (std::ostream& stream, Point &point)
	{
		return stream << "Point -> (X: " << point.x << ", Y: " << point.y << ")";
	}
}