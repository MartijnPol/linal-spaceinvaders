#ifndef GAME_UTILS_SHAPE_FACTORY_H
#define GAME_UTILS_SHAPE_FACTORY_H

#include <vector>
#include "Vector2D.h"
#include "Matrix.h"

using namespace math;

namespace utils
{
	class ShapeFactory
	{
	public:
		enum shape { spaceship, target, bullet };

		ShapeFactory() = default;
		~ShapeFactory() = default;

		template <typename T>
		static Matrix<T> get_shape(const shape shape)
		{
			const auto s = 2.5f;

			switch (shape)
			{
			case spaceship:
				return Matrix<T>(4, 10, { 0.0f, 0.0f, 5.0f, 3.0f, 0.0f, 3.0f, 5.0f, 0.0f, 5.0f, 3.0f,
										  5.0f, 0.0f, 0.0f, 3.0f, 0.0f, 3.0f, 0.0f, 5.0f, 0.0f, 3.0f,
										  0.0f, 5.0f, 0.0f, 3.0f, 5.0f, 3.0f, 0.0f, 0.0f, 0.0f, 3.0f,
										  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });

			case target:
				return Matrix<T>(4, 24, { s, -s, -s, s,  s, -s, -s,  s, s, -s, -s,  s,  s, -s, -s, s, -s,-s,-s,-s, s, s, s, s,
										  s,  s,  s, s, -s, -s, -s, -s, s,  s, -s, -s, -s, -s,  s, s,  s, s,-s,-s, s, s,-s,-s,
										 -s, -s,  s, s,  s,  s, -s, -s, s,  s,  s,  s, -s, -s, -s,-s,  s,-s,-s, s,-s, s, s,-s,
										  0,  0,  0, 0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0, 0, 0, 0, 0, 0, 0, 0 });

			case bullet:
				return Matrix<T>();

			default:
				return Matrix<T>();
			}
		}
	};
}

#endif