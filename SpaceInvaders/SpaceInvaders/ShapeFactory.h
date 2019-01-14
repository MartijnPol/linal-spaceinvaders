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
			const auto s = 25.0f;

			const auto w = 35.0f;
			const auto h = 60.0f;

			auto x = origin.x;
			auto y = origin.y;
			auto z = origin.z;

			switch (shape)
			{
			case spaceship:
				return Matrix<T>(4, 10, { x, x, x + w, x + h, x, x + h, x + w, x, x + w, x + h,
										  y + w, y, y, y + h, y, y + h, y, y + w, y, y + h,
										  z, z + w, z, z + h, z + w, z + h, z, z, z, z + h,
										  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });

			case cube:				//   A      B		C		D	   E	  F       G		  H
				return Matrix<T>(4, 8, { 10.0f, 110.0f, 110.0f, 10.0f, 10.0f, 110.0f, 110.0f, 10.0f,
										 10.0f, 10.0f,  10.0f,  10.0f, 110.0f,110.0f, 110.0f, 110.0f,
										 10.0f, 10.0f,  110.0f, 110.0f,10.0f, 10.0f,  110.0f, 110.0f,
										 1.0f,  1.0f,   1.0f,   1.0f,  1.0f,  1.0f,   1.0f,   1.0f
					});

							//return Matrix<T>(4, 24, { x + s, x - s, x - s, x + s, x + s, x - s, x - s, x + s, x + s, x - s, x - s, x + s, x + s, x - s, x - s, x + s, x - s, x - s, x - s, x - s, x + s, x + s, x + s, x + s,
							//						  y + s, y + s, y + s, y + s, y - s, y - s, y - s, y - s, y + s, y + s, y - s, y - s, y - s, y - s, y + s, y + s, y + s, y + s, y - s, y - s, y + s, y + s, y - s, y - s,
							//						  z - s, z - s, z + s, z + s, z + s, z + s, z - s, z - s, z + s, z + s, z + s, z + s, z - s, z - s, z - s, z - s, z + s, z - s, z - s, z + s, z - s, z + s, z + s, z - s,
							//						  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
			
			case bullet:
				return Matrix<T>();

			default:
				return Matrix<T>();
			}
		}
	};
}

#endif