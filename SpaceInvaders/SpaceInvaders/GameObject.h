﻿#ifndef GAME_GAME_OBJECT_H
#define GAME_GAME_OBJECT_H

#include "Matrix.h"

namespace game
{
	template <typename T>
	class GameObject
	{
	public:
		explicit GameObject() = default;

		void increase_turn(const float turn) noexcept { turn_value_ += turn; }
		void decrease_turn(const float turn) noexcept { turn_value_ -= turn; }
		float turn() const noexcept { return turn_value_; }

		void increase_roll(const float roll) noexcept { roll_value_ -= roll; }
		void decrease_roll(const float roll) noexcept { roll_value_ += roll; }
		float roll() const noexcept { return roll_value_; }

		void increase_dive(const float dive) noexcept { dive_value_ += dive; }
		void decrease_dive(const float dive) noexcept { dive_value_ -= dive; }
		float dive() const noexcept { return dive_value_; }

	protected:
		Matrix<T> object_matrix_;
		float turn_value_{};
		float roll_value_{};
		float dive_value_{};
	};
}

#endif