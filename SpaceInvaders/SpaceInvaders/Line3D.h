#ifndef LINE_3D
#define LINE_3D

struct Line3D
{
	Line3D() = default;
	Line3D(const Vector3D<float> s, const Vector3D<float> e) : start(s), end(e) {}
	Vector3D<float> start;
	Vector3D<float> end;

	float x() const noexcept { return end.x - start.x; }
	float y() const noexcept { return end.y - start.y; }
	float z() const noexcept { return end.z - start.z; }

	Line3D cross_product(Line3D other) const
	{
		Line3D result;
		result.start = { 0, 0, 0 };

		result.end.x = y() * other.z() - z() * other.y();
		result.end.y = z() * other.x() - x() * other.z();
		result.end.z = x() * other.y() - y() * other.x();

		return result;
	}

	Line3D translate(const Vector3D<float> other) const
	{
		return { {start.x + other.x, start.y + other.y, start.z + other.z},
			{end.x + other.x, end.y + other.y, end.z + other.z } };
	}
};

#endif
