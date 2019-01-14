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
		const auto rotation_vector = Vector3D<float>{ 2.0f, 2.0f, 2.0f };

		const auto t1 = atan2(rotation_vector.z, rotation_vector.x);
		const auto t2 = atan2(rotation_vector.y, sqrt(pow(rotation_vector.x, 2) + pow(rotation_vector.z, 2)));

		auto m1 = rotate_y(t1);
		auto m2 = rotate_z(t2);
		auto m3 = rotate_x(degrees_);
		auto m4 = rotate_z_negative(t2);
		auto m5 = rotate_y_negative(t2);

		auto rotate_result = m5 * m4 * m3 * m2 * m1 * object_matrix_;

		//object_matrix_ = rotate(result, { 2.0f, 2.0f, 0.0f });

		if (is_target_)
		{
			const auto width = graphics_.width();
			const auto height = graphics_.height();

			pulse();
			degrees_ += 0.1f;

			auto scale_vector = Vector3D<float>{ scale_factor_, scale_factor_, scale_factor_ };
			const auto scale_matrix = scale(scale_vector);
			auto result = scale_matrix * rotate_result;
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
