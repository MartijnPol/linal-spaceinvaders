#ifndef MATH_VECTOR_3D_H
#define MATH_VECTOR_3D_H

namespace math
{
	template<typename T>
	struct Vector3D
	{
		T x, y, z;

		Vector3D() = default;

		Vector3D(const T x, const T y, const T z)
			: x(x), y(y), z(z) {}

		Vector3D<T>& operator+=(const Vector3D<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;

			return *this;
		}

		Vector3D<T>& operator-=(const Vector3D<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;

			return *this;
		}

		Vector3D<T>& operator*=(const float scalar)
		{
			this->x = this->x * scalar;
			this->y = this->y * scalar;
			this->z = this->z * scalar;

			return *this;
		}

		float inner_product(const Vector3D<T> &other) const
		{
			return (x * other.x) + (y * other.y) + (z * other.z);
		}

		float angle(const Vector3D<T> &other) const
		{
			return std::acos(inner_product(other) / (length() * other.length()));
		}

		float length() const
		{
			return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
		}

		Vector3D<T> cross_product(const Vector3D<T> &other) const
		{
			auto cross_vector = Vector3D<T>{ 0, 0, 0 };

			cross_vector.x = (y * other.z - z * other.y);
			cross_vector.y = (z * other.x - x * other.z);
			cross_vector.z = (x * other.y - y * other.x);

			return cross_vector;
		}

		void normalize()
		{
			const auto vector_length = length();

			x /= vector_length;
			y /= vector_length;
			z /= vector_length;
		}
	};

	template <typename T>
	Vector3D<T> operator -(const Vector3D<T> vector)
	{
		auto inverted_vector = Vector3D<T>(0, 0, 0);

		inverted_vector.x = -vector.x;
		inverted_vector.y = -vector.y;
		inverted_vector.z = -vector.z;

		return inverted_vector;
	}

	template<class T>
	bool operator==(const Vector3D<T>& left, const Vector3D<T>& right)
	{
		if (left.x != right.x || left.y != right.y || left.z != right.z) {
			return false;
		}

		return true;
	}
}

#endif