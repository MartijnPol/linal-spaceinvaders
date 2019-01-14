#include "Cube.h"
#include "ShapeFactory.h"
#include "Line3D.h"

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
		auto rotation_vector = Vector3D<float>{ 2.0f, 2.0f, 2.0f };

		auto a_x = object_matrix_.at(0, 0);
		auto a_y = object_matrix_.at(1, 0);
		auto a_z = object_matrix_.at(2, 0);

		auto d_x = object_matrix_.at(0, 3);
		auto d_y = object_matrix_.at(1, 3);
		auto d_z = object_matrix_.at(2, 3);

		auto a = Vector3D<float>{ a_x, a_y , a_z };
		auto d = Vector3D<float>{ d_x, d_y , d_z };

		auto ad = Line3D{ a, d };

		auto h_x = object_matrix_.at(0, 7);
		auto h_y = object_matrix_.at(1, 7);
		auto h_z = object_matrix_.at(2, 7);

		auto h = Vector3D<float>{ h_x, h_y, h_z };

		auto hd = Line3D{ h, d };

		auto result = ad.cross_product(hd);

		auto const middle_point_x = (object_matrix_.max_x() + object_matrix_.min_x()) / 2;
		auto const middle_point_y = (object_matrix_.max_y() + object_matrix_.min_y()) / 2;
		auto const middle_point_z = (object_matrix_.max_z() + object_matrix_.min_z()) / 2;

		auto middle_vector = Vector3D<float>{ middle_point_x, middle_point_y, middle_point_z };
		auto translated = result.translate(middle_vector);

		graphics_.draw_line(translated.start, translated.end, graphics::colors::BLUE);

		const auto t1 = atan2(rotation_vector.z, rotation_vector.x);
		const auto t2 = atan2(rotation_vector.y, sqrt(pow(rotation_vector.x, 2) + pow(rotation_vector.z, 2)));

		auto back_matrix = translate(translated.start);

		auto m1 = rotate_y(t1);
		auto m2 = rotate_z(t2);
		auto m3 = rotate_x(degrees_);
		auto m4 = rotate_z_negative(t2);
		auto m5 = rotate_y_negative(t2);

		auto to_origin_vector = Vector3D<float>{ 0 - origin_.x, 0 - origin_.y, 0 - origin_.z };
		auto to_origin_matrix = translate(to_origin_vector);

		auto complete_matrix = to_origin_matrix * m1 * m2 * m3 * m4 * m5 * back_matrix;

		auto rotate_result = complete_matrix * object_matrix_;

		//object_matrix_ = rotate(result, { 2.0f, 2.0f, 0.0f });

		if (is_target_)
		{
			const auto width = graphics_.width();
			const auto height = graphics_.height();

			pulse();
			degrees_ += 0.10f;

			auto scale_vector = Vector3D<float>{ scale_factor_, scale_factor_, scale_factor_ };
			const auto scale_matrix = scale(scale_vector);
			auto result = scale_matrix * rotate_result;
			graphics_.draw_matrix(rotate_result, graphics::colors::RED);
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
