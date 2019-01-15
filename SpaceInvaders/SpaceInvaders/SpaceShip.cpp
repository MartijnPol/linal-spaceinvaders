#include "SpaceShip.h"
#include "ShapeFactory.h"
#include "Line3D.h"

using namespace utils;

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, Vector3D<float> origin)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::spaceship);
		object_matrix_ = translate(object_matrix_, origin);
		bullets_ = std::make_unique<std::vector<Bullet>>();
	}

	void SpaceShip::update()
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

		const auto t1 = Math::radius_to_degrees(std::atan2(translated.z(), translated.x()));
		const auto t2 = Math::radius_to_degrees(std::acosf(std::sqrtf(pow(translated.x(), 2) + pow(translated.z(), 2)) / translated.length()));

		const auto to_origin = translate(translated.start);
		const auto from_origin = translate(Vector3D<float>{-translated.start});

		const auto m1 = rotate_y(t1);
		const auto m2 = rotate_z(t2);
		const auto m3 = rotate_x(degrees_);
		const auto m4 = rotate_z(-t2);
		const auto m5 = rotate_y(-t2);

		const auto step_one = from_origin * object_matrix_;
		const auto step_two = m1 * step_one;
		const auto step_three = m2 * step_two;
		const auto step_four = m3 * step_three;
		const auto step_five = m4 * step_four;
		const auto step_six = m5 * step_five;
		auto step_seven = to_origin * step_six;

		degrees_ += 0.01f;

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

