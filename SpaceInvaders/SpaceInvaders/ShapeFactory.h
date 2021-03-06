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
		static Matrix<T> get_shape(const shape shape)
		{
			switch (shape)
			{
			case spaceship:

										// A     B	    C	   D	  E	  
				return Matrix<T>(4, 5, {   0.0f, 30.0f, 20.0f, 20.0f, 20.0f,
										   0.0f,  0.0f,  0.0f, 30.0f,  0.0f,
										   0.0f,  0.0f, 40.0f,  0.0f,  0.0f,
										   1.0f,  1.0f,  1.0f,  1.0f,  1.0f });

			case cube:			      
									  // A      B	   C		D	    E	  F      G	     H
				return Matrix<T>(4, 8, { 0.0f,  30.0f, 30.0f,   0.0f,   0.0f, 30.0f, 30.0f,  0.0f,
										 0.0f,   0.0f,  0.0f,   0.0f,  30.0f, 30.0f, 30.0f, 30.0f,
										 0.0f,   0.0f, 30.0f,  30.0f,   0.0f,  0.0f, 30.0f, 30.0f,
										 1.0f,   1.0f,  1.0f,   1.0f,   1.0f,  1.0f,  1.0f,  1.0f });

			case bullet:
									  // A      B	   C	    D	    E	  F      G		 H
				return Matrix<T>(4, 8, { 0.0f,  10.0f, 10.0f,   0.0f,   0.0f, 10.0f, 10.0f,  0.0f,
										 0.0f,   0.0f,  0.0f,   0.0f,  10.0f, 10.0f, 10.0f, 10.0f,
										 0.0f,   0.0f, 10.0f,  10.0f,   0.0f,  0.0f, 10.0f, 10.0f,
										 1.0f,   1.0f,  1.0f,   1.0f,   1.0f,  1.0f,  1.0f,  1.0f });
			default:
				return Matrix<T>();
			}
		}
	};
}

#endif