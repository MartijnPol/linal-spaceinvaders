#ifndef MATH_MATH_H
#define MATH_MATH_H

namespace math
{
	struct Math
	{
		static float degrees_to_radius(const float degrees)
		{
			return degrees * (M_PI / 180.0f);
		}
	};
}

#endif