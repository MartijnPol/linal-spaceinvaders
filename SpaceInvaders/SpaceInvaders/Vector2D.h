#ifndef MATH_VECTOR_2D_H
#define MATH_VECTOR_2D_H

#include <ostream>
#include <functional>

namespace math
{
	template<typename T>
	struct Vector2D
	{
		T x, y;

		Vector2D(const T x, const T y)
			: x(x), y(y) {};

		Vector2D<T>& operator+=(const Vector2D<T> &other)
		{
			this->x += other.x;
			this->y += other.y;

			return *this;
		}

		Vector2D<T>& operator-=(const Vector2D<T> &other)
		{
			this->x -= other.x;
			this->y -= other.y;

			return *this;
		}

		Vector2D<T>& operator*=(const Vector2D<T> &other)
		{
			this->x *= other.x;
			this->y *= other.y;

			return *this;
		}

		Vector2D<T>& operator*=(const float scalar)
		{
			this->x = x * scalar;
			this->y = y * scalar;

			return *this;
		}

		/*
		 * Berekend het inproduct van deze vector en een andere.
		 * Hiervoor worden de x-waarden en de y-waarden vermenigvuldigd en bij elkaar opgeteld.
		 */
		float inner_product(const Vector2D<T> &other) const
		{
			return (x * other.x) + (y * other.y);
		}

		/*
		 * Berekend de hoek tussen deze vector en een andere.
		 * Daarvoor wordt het inproduct van deze twee vectoren gedeeld
		 * door de lengte van deze vector maal de lengte van de andere vector.
		 * Vervolgens wordt de arccosinus over deze berekening gedaan waardoor het aantal graden bekend is.
		 */
		float angle(const Vector2D<T> &other) const
		{
			return std::acos(inner_product(other) / (length() * other.length()));
		}

		/*
		 * Deze functie retourneert de lengte van deze Vector.
		 * Hiervoor worden de kwadraten van de x en de y-waarden bij elkaar opgeteld.
		 * Vervolgens wordt hier de wortel van getrokken.
		 */
		float length() const
		{
			return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
		}

		// Vector die loodrecht op deze vector staat.
		Vector2D<T> perpendicular() const
		{
			Vector2D<T> perpendicular_vector({ this->x, this->y });

			perpendicular_vector.x = y;
			perpendicular_vector.y = -x;

			return perpendicular_vector;
		}
	};

	template <typename T>
	std::ostream& operator << (std::ostream &stream, Vector2D<T> &vector)
	{
		return stream << "Vector -> (X: " << vector.x << ", Y: " << vector.y << ")";
	}

	template<class T> Vector2D<T> operator + (const Vector2D<T>& l, const Vector2D<T>& r) { return { l.x + r.x, l.y + r.y }; };
	template<class T> Vector2D<T> operator - (const Vector2D<T>& l, const Vector2D<T>& r) { return { l.x - r.x, l.y - r.y }; };
	template<class T> Vector2D<T> operator * (T s, const Vector2D<T>& v) { return { s*v.x, s*v.y }; };
	template<class T> Vector2D<T> operator * (const Vector2D<T>& v, T s) { return { v.x*s, v.y*s }; };
	template<class T> Vector2D<T> operator / (const Vector2D<T>& v, T s) { return { v.x / s, v.y / s }; };
}



#endif