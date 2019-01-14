#include "Cube.h"
#include "ShapeFactory.h"
#include <iostream>

using namespace utils;

namespace game
{
	Cube::Cube(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, const Vector3D<float> origin, const bool is_target)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color), is_target_(is_target)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::cube);
	}

	void Cube::update()
	{
		object_matrix_ = rotate(object_matrix_, { turn(), dive(), roll() });

		if (is_target_)
		{
			pulse();
			Vector3D<float> scale_vector(scale_factor_, scale_factor_, scale_factor_);
			std::cout << scale_factor_ << "\n";
			auto scaled_target = scale(object_matrix_, scale_vector);
			graphics_.draw_matrix(scaled_target, graphics::colors::RED);
		}
		else
		{
			graphics_.draw_matrix(object_matrix_, color_);
		}
	}

	void Cube::pulse()
	{
		if (scale_factor_ <= max_scale_factor_ && !reversed_)
		{
			scale_factor_ += pulse_speed_;
			if (scale_factor_ >= max_scale_factor_) reversed_ = true;
		}
		else if (reversed_)
		{
			scale_factor_ -= pulse_speed_;
			if (scale_factor_ <= 1.0f) reversed_ = false;
		}
	}
}
