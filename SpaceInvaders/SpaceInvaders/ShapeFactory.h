#ifndef UTILS_SHAPE_FACTORY_H
#define UTILS_SHAPE_FACTORY_H

#include <vector>
#include "Point.h"
#include "Vector2D.h"

using namespace math;

namespace utils
{
	class ShapeFactory
	{
	public:
		enum shape { triangle, rectangle, rocket };

		ShapeFactory() = default;
		~ShapeFactory() = default;

		static std::vector<std::unique_ptr<Vector2D>> get_shape(const Point origin, const shape shape)
		{
			std::vector<std::unique_ptr<Vector2D>> vectors;

			switch (shape)
			{
			case triangle:
				vectors.push_back(std::make_unique<Vector2D>(origin, -4, 0));
				vectors.push_back(std::make_unique<Vector2D>(origin, -2, 4));
				vectors.push_back(std::make_unique<Vector2D>(Point{ origin.x - 4, origin.y }, 2, 4));
				break;

			case rectangle:
				vectors.push_back(std::make_unique<Vector2D>(Point(1, 1), 0, 1));
				vectors.push_back(std::make_unique<Vector2D>(Point(1, 2), 1.5f, 0));
				vectors.push_back(std::make_unique<Vector2D>(Point(2.5f, 2), 0, -1));
				vectors.push_back(std::make_unique<Vector2D>(Point(2.5f, 1), -1.5f, 0));
				break;

			case rocket:
				vectors.push_back(std::make_unique<Vector2D>(origin, -6, 0));
				vectors.push_back(std::make_unique<Vector2D>(origin, -2, 6));
				vectors.push_back(std::make_unique<Vector2D>(Point{ origin.x - 6, origin.y }, 2, 6));

			default:;
			}

			return vectors;
		}
	};
}

#endif