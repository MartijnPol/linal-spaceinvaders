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
		const auto b = Vector3D<float>{ b_x, b_y, b_z };

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

		// D
		const auto d_x = original_matrix_.at(0, 3);
		const auto d_y = original_matrix_.at(1, 3);
		const auto d_z = original_matrix_.at(2, 3);
		const auto d = Vector3D<float>{ d_x, d_y, d_z };

		auto ab = Line3D{ a, d };
		const auto bd = Line3D{ b, d };

		auto result = ab.cross_product(bd);

		auto const middle_point_x = (original_matrix_.max(0) + original_matrix_.min(0)) / 2;
		auto const middle_point_y = (original_matrix_.max(1) + original_matrix_.min(1)) / 2;
		auto const middle_point_z = (original_matrix_.max(2) + original_matrix_.min(2)) / 2;

		const auto middle_vector = Vector3D<float>{ middle_point_x, middle_point_y, middle_point_z };
		const auto translated = result.translate(middle_vector);
		handle(translated);
	}


	void SpaceShip::pitch()
	{
		// C
		const auto a_x = original_matrix_.at(0, 2);
		const auto a_y = original_matrix_.at(1, 2);
		const auto a_z = original_matrix_.at(2, 2);
		const auto a = Vector3D<float>{ a_x, a_y , a_z };

		// D
		const auto d_x = original_matrix_.at(0, 3);
		const auto d_y = original_matrix_.at(1, 3);
		const auto d_z = original_matrix_.at(2, 3);
		const auto d = Vector3D<float>{ d_x, d_y , d_z };

		// E
		const auto h_x = original_matrix_.at(0, 4);
		const auto h_y = original_matrix_.at(1, 4);
		const auto h_z = original_matrix_.at(2, 4);
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

	void SpaceShip::handle(Line3D translated)
	{
		if (help_line_)
		{
			graphics_.draw_line(translated.start, translated.end, graphics::colors::BLUE);
		}

		rotate(translated);
	}

	void SpaceShip::update()
	{
		draw_matrix_ = original_matrix_;
		degrees_ += 0.05f;

		yaw();

		draw_matrix_ = translate(draw_matrix_, origin_);
		graphics_.draw_matrix(draw_matrix_, color_);

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

