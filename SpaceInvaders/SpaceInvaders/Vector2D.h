#ifndef MATH_VECTOR_2D_H
#define MATH_VECTOR_2D_H

#include "Point.h"
#include <ostream>
#include <functional>

namespace math
{
	struct Vector2D
	{
		Point origin{ 0, 0 };
		float x = 0;
		float y = 0;

		Vector2D(Point origin, float x, float y)
			: origin(origin), x(x), y(y) {};

		Vector2D& operator+=(const Vector2D &other)
		{
			this->x += other.x;
			this->y += other.y;

			return *this;
		}

		Vector2D& operator-=(const Vector2D &other)
		{
			this->x -= other.x;
			this->y -= other.y;

			return *this;
		}

		Vector2D& operator*=(const Vector2D &other)
		{
			this->x *= other.x;
			this->y *= other.y;

			return *this;
		}

		Vector2D& operator*=(const float scalar)
		{
			this->x = x * scalar;
			this->y = y * scalar;

			return *this;
		}

		/*
		 * Berekend het inproduct van deze vector en een andere.
		 * Hiervoor worden de x-waarden en de y-waarden vermenigvuldigd en bij elkaar opgeteld.
		 */
		float inner_product(const Vector2D &other) const
		{
			return (x * other.x) + (y * other.y);
		}

		/*
		 * Berekend de hoek tussen deze vector en een andere.
		 * Daarvoor wordt het inproduct van deze twee vectoren gedeeld 
		 * door de lengte van deze vector maal de lengte van de andere vector.
		 * Vervolgens wordt de arccosinus over deze berekening gedaan waardoor het aantal graden bekend is.
		 */
		float angle(const Vector2D &other) const
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
		Vector2D perpendicular() const
		{
			Vector2D perpendicular_vector({ this->origin.x, this->origin.y }, 0, 0);

			perpendicular_vector.x = y;
			perpendicular_vector.y = -x;

			return perpendicular_vector;
		}
	};

	inline std::ostream& operator << (std::ostream &stream, Vector2D &vector)
	{
		return stream << "Vector -> (X: " << vector.x << ", Y: " << vector.y << ")";
	}
}

#endif