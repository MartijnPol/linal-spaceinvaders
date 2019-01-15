#ifndef GAME_GAME_OBJECT_H
#define GAME_GAME_OBJECT_H

#include "Matrix.h"

namespace game
{
	template <typename T>
	class GameObject
	{
	public:
		explicit GameObject(Vector3D<T> origin) : origin_(origin) {}

		void switch_help_line()
		{
			help_line_ = !help_line_;
		}

		void rotate(Line3D line, float degrees)
		{
			draw_matrix_ = math::rotate(draw_matrix_, line, degrees);
			const auto vector = Vector3D<float>{ line.x(), line.y(), line.z() };
			heading_ = math::rotate(vector) * heading_;
		}

		void accelerate()
		{
			draw_matrix_ = math::translate(draw_matrix_, heading_);
		}


	protected:
		Matrix<T> original_matrix_;
		Matrix<T> draw_matrix_;
		Vector3D<T> origin_;
		Vector3D<T> heading_{ 0.0f, 0.0f, 1.0f };

		float degrees_{ 0.0f };
		bool help_line_{};
	};
}

#endif