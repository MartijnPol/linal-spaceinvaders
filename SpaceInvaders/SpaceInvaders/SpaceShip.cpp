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
		// Get points in shape
		const auto a = original_matrix_.get_point_vector(0);
		const auto b = original_matrix_.get_point_vector(1);
		const auto c = original_matrix_.get_point_vector(2);

		auto ab = Line3D{ a, b };
		const auto bc = Line3D{ b, c };

		auto result = ab.cross_product(bc);

		const auto middle_vector = original_matrix_.get_middle_vector();
		const auto translated = result.translate(middle_vector);
		handle(translated, yaw_degrees);
	}

	void SpaceShip::reset()
	{
		pitch_up = false;
		pitch_down = false;
		yaw_left = false;
		yaw_right = false;
		roll_left = false;
		roll_right = false;
	}

	void SpaceShip::roll()
	{
		// Get points in shape
		const auto a = original_matrix_.get_point_vector(0);
		const auto b = original_matrix_.get_point_vector(1);
		const auto d = original_matrix_.get_point_vector(3);

		auto ab = Line3D{ a, d };
		const auto bd = Line3D{ b, d };

		auto result = ab.cross_product(bd);

		const auto middle_vector = original_matrix_.get_middle_vector();
		const auto translated = result.translate(middle_vector);
		handle(translated, roll_degrees);
	}

	void SpaceShip::pitch()
	{
		// Get points in shape
		const auto c = original_matrix_.get_point_vector(2);
		const auto d = original_matrix_.get_point_vector(3);
		const auto e = original_matrix_.get_point_vector(4);

		auto ad = Line3D{ c, d };
		const auto hd = Line3D{ d, e };

		auto result = ad.cross_product(hd);

		const auto middle_vector = original_matrix_.get_middle_vector();
		const auto translated = result.translate(middle_vector);
		handle(translated, pitch_degrees);
	}

	void SpaceShip::handle(const Line3D translated, const float degrees)
	{
		if (help_line_)
		{
			graphics_.draw_line(translated.start, translated.end, graphics::colors::BLUE);
		}

		rotate(translated, degrees);
	}

	void SpaceShip::update()
	{
		draw_matrix_ = original_matrix_;

		if (pitch_up)
		{
			pitch_degrees -= speed_;
		}

		if (pitch_down)
		{
			pitch_degrees += speed_;
		}

		if (yaw_left)
		{
			yaw_degrees += speed_;
		}

		if (yaw_right)
		{
			yaw_degrees -= speed_;
		}

		if (roll_left)
		{
			roll_degrees -= speed_;
		}

		if (roll_right)
		{
			roll_degrees += speed_;
		}

		pitch();
		roll();
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

		reset();
	}

	void SpaceShip::fire_bullet()
	{
		const auto bullet = Bullet{ graphics_, graphics::colors::RED, origin_ };
		bullets_->push_back(bullet);
	}
}

