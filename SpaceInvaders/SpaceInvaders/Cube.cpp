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
	}

	void Cube::yaw()
	{
		// Get points in shape
		const auto a = original_matrix_.get_point_vector(0);
		const auto b = original_matrix_.get_point_vector(1);
		const auto c = original_matrix_.get_point_vector(2);
		
		auto ab = Line3D{ a, b };
		const auto bc = Line3D{ b, c };
		auto result = ab.cross_product(bc);

		const auto middle_vector = original_matrix_.get_middle_vector();
		const auto translated = result.translate(middle_vector);
		handle(translated);
	}

	void Cube::roll()
	{
		// Get points in shape
		const auto a = original_matrix_.get_point_vector(0);
		const auto b = original_matrix_.get_point_vector(1);
		const auto f = original_matrix_.get_point_vector(5);

		auto ab = Line3D{ a, b };
		const auto bf = Line3D{ b, f };

		auto result = ab.cross_product(bf);

		const auto middle_vector = original_matrix_.get_middle_vector();
		const auto translated = result.translate(middle_vector);
		handle(translated);
	}


	void Cube::pitch()
	{
		// Get points in shape
		const auto a = original_matrix_.get_point_vector(0);
		const auto d = original_matrix_.get_point_vector(3);
		const auto h = original_matrix_.get_point_vector(7);

		auto ad = Line3D{ a, d };
		const auto hd = Line3D{ h, d };

		auto result = ad.cross_product(hd);

		const auto middle_vector = original_matrix_.get_middle_vector();
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

		if (is_target_)
		{
			pulse();
			auto scale_vector = Vector3D<float>(scale_factor_, scale_factor_, scale_factor_);
			draw_matrix_ = scale(draw_matrix_, scale_vector);
		}

		draw_matrix_ = translate(draw_matrix_, origin_);
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
