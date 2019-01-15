#include "Cube.h"
#include "ShapeFactory.h"
#include "Line3D.h"
#include <thread>

using namespace utils;

namespace game
{
	Cube::Cube(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, const Vector3D<float> origin, const bool is_target)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color), is_target_(is_target)
	{
		original_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::cube);
		//translate(object_matrix_, origin);
	}

	void Cube::yaw()
	{
		// A
		const auto a_x = original_matrix_.at(0, 0);
		const auto a_y = original_matrix_.at(1, 0);
		const auto a_z = original_matrix_.at(2, 0);
		const auto a = Vector3D<float>{ a_x, a_y , a_z };

		// B
		const auto b_x = original_matrix_.at(0, 1);
		const auto b_y = original_matrix_.at(1, 1);
		const auto b_z = original_matrix_.at(2, 1);
		const auto b = Vector3D<float>{ b_x, b_y , b_z };

		// C
		const auto c_x = original_matrix_.at(0, 2);
		const auto c_y = original_matrix_.at(1, 2);
		const auto c_z = original_matrix_.at(2, 2);
		const auto c = Vector3D<float>{ c_x, c_y, c_z };

		auto ab = Line3D{ a, b };
		const auto bc = Line3D{ b, c };

		auto result = ab.cross_product(bc);

		auto const middle_point_x = (original_matrix_.max(0) + original_matrix_.min(0)) / 2;
		auto const middle_point_y = (original_matrix_.max(1) + original_matrix_.min(1)) / 2;
		auto const middle_point_z = (original_matrix_.max(2) + original_matrix_.min(2)) / 2;

		const auto middle_vector = Vector3D<float>{ middle_point_x, middle_point_y, middle_point_z };
		const auto translated = result.translate(middle_vector);
		handle(translated);
	}

	void Cube::roll()
	{
		// A
		const auto a_x = original_matrix_.at(0, 0);
		const auto a_y = original_matrix_.at(1, 0);
		const auto a_z = original_matrix_.at(2, 0);
		const auto a = Vector3D<float>{ a_x, a_y , a_z };

		// B
		const auto b_x = original_matrix_.at(0, 1);
		const auto b_y = original_matrix_.at(1, 1);
		const auto b_z = original_matrix_.at(2, 1);
		const auto b = Vector3D<float>{ b_x, b_y , b_z };

		// F
		const auto f_x = original_matrix_.at(0, 5);
		const auto f_y = original_matrix_.at(1, 5);
		const auto f_z = original_matrix_.at(2, 5);
		const auto f = Vector3D<float>{ f_x, f_y, f_z };

		auto ab = Line3D{ a, b };
		const auto bf = Line3D{ b, f };

		auto result = ab.cross_product(bf);

		auto const middle_point_x = (original_matrix_.max(0) + original_matrix_.min(0)) / 2;
		auto const middle_point_y = (original_matrix_.max(1) + original_matrix_.min(1)) / 2;
		auto const middle_point_z = (original_matrix_.max(2) + original_matrix_.min(2)) / 2;

		const auto middle_vector = Vector3D<float>{ middle_point_x, middle_point_y, middle_point_z };
		const auto translated = result.translate(middle_vector);
		handle(translated);
	}


	void Cube::pitch()
	{
		// A
		const auto a_x = original_matrix_.at(0, 0);
		const auto a_y = original_matrix_.at(1, 0);
		const auto a_z = original_matrix_.at(2, 0);
		const auto a = Vector3D<float>{ a_x, a_y , a_z };

		// D
		const auto d_x = original_matrix_.at(0, 3);
		const auto d_y = original_matrix_.at(1, 3);
		const auto d_z = original_matrix_.at(2, 3);
		const auto d = Vector3D<float>{ d_x, d_y , d_z };

		// H
		const auto h_x = original_matrix_.at(0, 7);
		const auto h_y = original_matrix_.at(1, 7);
		const auto h_z = original_matrix_.at(2, 7);
		const auto h = Vector3D<float>{ h_x, h_y, h_z };

		auto ad = Line3D{ a, d };
		const auto hd = Line3D{ h, d };

		auto result = ad.cross_product(hd);

		auto const middle_point_x = (original_matrix_.max(0) + original_matrix_.min(0)) / 2;
		auto const middle_point_y = (original_matrix_.max(1) + original_matrix_.min(1)) / 2;
		auto const middle_point_z = (original_matrix_.max(2) + original_matrix_.min(2)) / 2;

		const auto middle_vector = Vector3D<float>{ middle_point_x, middle_point_y, middle_point_z };
		const auto translated = result.translate(middle_vector);
		handle(translated);
	}

	void Cube::handle(Line3D translated)
	{
		if (help_line_)
		{
			graphics_.draw_line(translated.start, translated.end, graphics::colors::BLUE);
		}

		rotate(translated);

		const auto t1 = std::atan2(translated.z(), translated.x());
		const auto t2 = std::acosf(std::sqrtf(pow(translated.x(), 2) + pow(translated.z(), 2)) / translated.length());

		const auto to_origin = translate(translated.start);
		const auto from_origin = translate(Vector3D<float>{-translated.start});

		if (is_target_)
		{
			auto scale_vector = Vector3D<float>{ scale_factor_, scale_factor_, 0.0f };

			const auto from = from_origin * draw_matrix_;
			const auto scale_matrix = scale(scale_vector);
			const auto result = scale_matrix * from;
			draw_matrix_ = to_origin * result;
		}
	}


	void Cube::update()
	{
		draw_matrix_ = original_matrix_;
		degrees_ += 0.05f;

		pitch();
		roll();

		draw_matrix_ = translate(draw_matrix_, origin_);


		if (is_target_)
		{
			pulse();
			auto scale_vector = Vector3D<float>(scale_factor_, scale_factor_, scale_factor_);
			draw_matrix_ = scale(draw_matrix_, scale_vector);
		}

		graphics_.draw_matrix(draw_matrix_, color_);
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
