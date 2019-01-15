﻿#ifndef GAME_GAME_OBJECT_H
#define GAME_GAME_OBJECT_H

#include "Matrix.h"

namespace game
{
	template <typename T>
	class GameObject
	{
	public:
		explicit GameObject(Vector3D<T> origin) : origin_(origin) {}

		void increase_turn(const float turn) noexcept { turn_value_ += turn; }
		void decrease_turn(const float turn) noexcept { turn_value_ -= turn; }
		float turn() const noexcept { return turn_value_; }

		void increase_roll(const float roll) noexcept { roll_value_ -= roll; }
		void decrease_roll(const float roll) noexcept { roll_value_ += roll; }
		float roll() const noexcept { return roll_value_; }

		void increase_dive(const float dive) noexcept { dive_value_ += dive; }
		void decrease_dive(const float dive) noexcept { dive_value_ -= dive; }
		float dive() const noexcept { return dive_value_; }

		void increase_move(const float move) noexcept { move_value_ += move; }
		void decrease_move(const float move) noexcept { move_value_ -= move; }
		float move() const noexcept { return move_value_; }

		void switch_help_line()
		{
			help_line_ = !help_line_;
		}

		void reset()
		{
			move_value_ = 0.0f;
			dive_value_ = 0.0f;
			roll_value_ = 0.0f;
			turn_value_ = 0.0f;
		}

		void rotate(Line3D line)
		{
			draw_matrix_ = math::rotate(draw_matrix_, line, degrees_);
			heading_ = math::rotate(line, degrees_) * heading_;
		}

	protected:
		Matrix<T> original_matrix_;
		Matrix<T> draw_matrix_;
		Vector3D<T> origin_;
		Vector3D<T> heading_{ 0.0f, 0.0f, 1.0f };

		float degrees_{ 0.0f };
		float turn_value_{};
		float roll_value_{};
		float dive_value_{};
		float move_value_{};
		bool help_line_{};
	};
}

#endif