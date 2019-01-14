#ifndef MATH_MATH_H
#define MATH_MATH_H

#ifndef PI
#define PI 3.14159265358979323846
#endif

namespace math
{
	struct Math
	{
		static float degrees_to_radius(const float degrees)
		{
			return degrees * (PI / 180.0f);
		}

		static float radius_to_degrees(const float radius)
		{
			return radius / (PI / 180.0f);
		}
	};
}

#endif