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
		translate(object_matrix_, origin);
	}

	void Cube::update()
	{
		const auto a_x = object_matrix_.at(0, 0);
		const auto a_y = object_matrix_.at(1, 0);
		const auto a_z = object_matrix_.at(2, 0);

		const auto d_x = object_matrix_.at(0, 3);
		const auto d_y = object_matrix_.at(1, 3);
		const auto d_z = object_matrix_.at(2, 3);

		const auto a = Vector3D<float>{ a_x, a_y , a_z };
		const auto d = Vector3D<float>{ d_x, d_y , d_z };
		auto ad = Line3D{ a, d };

		const auto h_x = object_matrix_.at(0, 7);
		const auto h_y = object_matrix_.at(1, 7);
		const auto h_z = object_matrix_.at(2, 7);

		const auto h = Vector3D<float>{ h_x, h_y, h_z };
		const auto hd = Line3D{ h, d };

		auto result = ad.cross_product(hd);

		auto const middle_point_x = (object_matrix_.max(0) + object_matrix_.min(0)) / 2;
		auto const middle_point_y = (object_matrix_.max(1) + object_matrix_.min(1)) / 2;
		auto const middle_point_z = (object_matrix_.max(2) + object_matrix_.min(2)) / 2;

		const auto middle_vector = Vector3D<float>{ middle_point_x, middle_point_y, middle_point_z };
		auto translated = result.translate(middle_vector);

		graphics_.draw_line(translated.start, translated.end, graphics::colors::BLUE);

		const auto t1 = Math::radius_to_degrees(std::atan2(translated.z(), translated.x()));
		const auto t2 = Math::radius_to_degrees(std::acosf(std::sqrtf(pow(translated.x(), 2) + pow(translated.z(), 2)) / translated.length()));

		const auto to_origin = translate(translated.start);

		const auto m1 = rotate_y(t1);
		const auto m2 = rotate_z(t2);
		const auto m3 = rotate_x(degrees_);
		const auto m4 = rotate_z_negative(t2);
		const auto m5 = rotate_y_negative(t2);

		const auto from_origin = translate(Vector3D<float>{-translated.start.x, -translated.start.y, -translated.start.z});

		auto transform_matrix = from_origin * to_origin;

		//graphics_.draw_matrix(object_matrix_, graphics::colors::RED);


		auto tst1 = from_origin * object_matrix_;
		//graphics_.draw_matrix(tst1, graphics::colors::GREEN);

		auto tst2 = m1 * tst1;
		//graphics_.draw_matrix(tst2, graphics::colors::GREEN);

		auto tst3 = m2 * tst2;
		//graphics_.draw_matrix(tst3, graphics::colors::GREEN);

		auto tst4 = m3 * tst3;

		auto tst5 = m4 * tst4;
		//graphics_.draw_matrix(tst5, graphics::colors::RED);

		auto tst6 = m5 * tst5;
		//graphics_.draw_matrix(tst6, graphics::colors::GRAY);

		auto tst7= to_origin * tst6;
		//graphics_.draw_matrix(tst7, graphics::colors::GRAY);


		//object_matrix_ = rotate(result, { 2.0f, 2.0f, 0.0f });

		if (is_target_)
		{
			pulse();
			degrees_ += 0.10f;

			auto scale_vector = Vector3D<float>{ scale_factor_, scale_factor_, scale_factor_ };
			const auto scale_matrix = scale(scale_vector);
			auto result = scale_matrix * tst7;
			graphics_.draw_matrix(result, color_);
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
