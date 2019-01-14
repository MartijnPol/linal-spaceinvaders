#ifndef GAME_UTILS_SHAPE_FACTORY_H
#define GAME_UTILS_SHAPE_FACTORY_H

#include "Matrix.h"

using namespace math;

namespace utils
{
	class ShapeFactory
	{
	public:
		enum shape { spaceship, cube, bullet };

		ShapeFactory() = default;
		~ShapeFactory() = default;

		template <typename T>
		static Matrix<T> get_shape(const shape shape, Vector3D<T> origin)
		{
			const auto s = 2.5f;

			auto x = origin.x;
			auto y = origin.y;
			auto z = origin.z;

			switch (shape)
			{
			case spaceship:
				return Matrix<T>(4, 10, { x, x, x + 5.0f, x + 3.0f, x, x + 3.0f, x + 5.0f, x, x + 5.0f, x + 3.0f,
										  y + 5.0f, y, y, y + 3.0f, y, y + 3.0f, y, y + 5.0f, y, y + 3.0f,
										  z, z + 5.0f, z, z + 3.0f, z + 5.0f, z + 3.0f, z, z, z, z + 3.0f,
										  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });

			case cube:
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