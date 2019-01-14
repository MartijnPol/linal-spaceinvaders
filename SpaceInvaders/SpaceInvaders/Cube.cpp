#include "Cube.h"
#include "ShapeFactory.h"

using namespace utils;

namespace game
{
	Cube::Cube(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, const Vector3D<float> origin, const bool is_target)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color), is_target_(is_target)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::cube, origin);
	}

	void Cube::update()
	{
		object_matrix_ = rotate(object_matrix_, { 2.0f, 2.0f, 0.0f });

		if (is_target_)
		{
			const auto width = graphics_.width();
			const auto height = graphics_.height();

			pulse();

			auto scale_vector = Vector3D<float>{ scale_factor_, scale_factor_, scale_factor_ };
			const auto scale_matrix = scale(scale_vector);
			auto result = scale_matrix * object_matrix_;
			graphics_.draw_matrix(result, graphics::colors::RED);
		}
		else
		{
			graphics_.draw_matrix(object_matrix_, color_);
		}

		reset();
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
