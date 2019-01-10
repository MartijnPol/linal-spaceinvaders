#ifndef MATH_MATH_H
#define MATH_MATH_H

namespace math
{
	struct Math
	{
		static constexpr float PI = 3.14159265358979323846f;
		static float degrees_to_radius(const float degrees)
		{
			return degrees * (PI / 180.0f);
		}
	};
}

#endif