#ifndef MATH_MATH_H
#define MATH_MATH_H

namespace math
{
	struct Math
	{
		static constexpr float pi = 3.14159265358979323846f;

		static float degrees_to_radius(float degrees)
		{
			return degrees * (pi / 180.0f);
		}
	};
}

#endif