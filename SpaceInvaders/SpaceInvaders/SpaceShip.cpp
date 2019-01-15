#include "SpaceShip.h"
#include "ShapeFactory.h"
#include "Line3D.h"

using namespace utils;

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, Vector3D<float> origin)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color)
	{
		original_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::spaceship);
		bullets_ = std::make_unique<std::vector<Bullet>>();
	}

	void SpaceShip::yaw()
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
		rotate(translated);
	}

	void SpaceShip::roll()
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
		rotate(translated);
	}


	void SpaceShip::pitch()
	{
		// A
		const auto a_x = original_matrix_.at(0, 0);
		const auto a_y = original_matrix_.at(1, 0);
		const auto a_z = original_matrix_.at(2, 0);
		const auto a = Vector3D<float>{ a_x, a_y , a_z };

		// B
		const auto b_x = original_matrix_.at(0, 3);
		const auto b_y = original_matrix_.at(1, 3);
		const auto b_z = original_matrix_.at(2, 3);
		const auto b = Vector3D<float>{ b_x, b_y , b_z };

		// C
		const auto c_x = original_matrix_.at(0, 7);
		const auto c_y = original_matrix_.at(1, 7);
		const auto c_z = original_matrix_.at(2, 7);
		const auto c = Vector3D<float>{ c_x, c_y, c_z };

		auto ab = Line3D{ a, b };
		const auto bc = Line3D{ b, c };

		auto result = ab.cross_product(bc);

		auto const middle_point_x = (original_matrix_.max(0) + original_matrix_.min(0)) / 2;
		auto const middle_point_y = (original_matrix_.max(1) + original_matrix_.min(1)) / 2;
		auto const middle_point_z = (original_matrix_.max(2) + original_matrix_.min(2)) / 2;

		const auto middle_vector = Vector3D<float>{ middle_point_x, middle_point_y, middle_point_z };
		const auto translated = result.translate(middle_vector);
		rotate(translated);
	}

	void SpaceShip::rotate(Line3D translated)
	{
		if (help_line_)
		{
			graphics_.draw_line(translated.start, translated.end, graphics::colors::BLUE);
		}

		const auto t1 = std::atan2(translated.z(), translated.x());
		const auto t2 = std::acosf(std::sqrtf(pow(translated.x(), 2) + pow(translated.z(), 2)) / translated.length());

		const auto to_origin = translate(translated.start);
		const auto from_origin = translate(Vector3D<float>{-translated.start});

		const auto m1 = rotate_y(t1);
		const auto m2 = rotate_z(t2);
		const auto m3 = rotate_x(degrees_);
		const auto m4 = rotate_z(-t2);
		const auto m5 = rotate_y(-t2);

		auto step_one = from_origin * draw_matrix_;
		//graphics_.draw_matrix(step_one, graphics::colors::RED);
		auto step_two = m1 * step_one;
		// graphics_.draw_matrix(step_two, graphics::colors::BLUE);

		auto step_three = m2 * step_two;
		// graphics_.draw_matrix(step_three, graphics::colors::WHITE);

		auto step_four = m3 * step_three;
		// graphics_.draw_matrix(step_four, graphics::colors::GREEN);

		auto step_five = m4 * step_four;
		// graphics_.draw_matrix(step_five, graphics::colors::GRAY);

		auto step_six = m5 * step_five;
		//graphics_.draw_matrix(step_six, graphics::colors::WHITE);

		draw_matrix_ = to_origin * step_six;
	}


	void SpaceShip::update()
	{
		draw_matrix_ = original_matrix_;
		degrees_ += 0.2f;
		yaw();

		draw_matrix_ = translate(draw_matrix_, origin_);
		graphics_.draw_matrix(draw_matrix_, color_);
		graphics_.draw_line(translated.start, translated.end, graphics::colors::BLUE);
		graphics_.draw_matrix(object_matrix_, color_);

		if (bullets_->size() >= 10)
		{
			bullets_->erase(bullets_->begin());
		}
		for (auto& bullet : *bullets_)
		{
			bullet.update();
		}
	}

	void SpaceShip::fire_bullet()
	{
		const auto bullet = Bullet{ graphics_, graphics::colors::RED, origin_ };
		bullets_->push_back(bullet);
	}
}

