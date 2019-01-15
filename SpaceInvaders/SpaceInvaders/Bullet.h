#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "GraphicsFacade.h"
#include "GameObject.h"
#include "ShapeFactory.h"
#include "Line3D.h"

using namespace math;
using namespace utils;

namespace game
{
	class Bullet : public GameObject<float>
	{
	public:
		Bullet(graphics::GraphicsFacade& graphics_facade, graphics::Color color, Vector3D<float> origin)
			: GameObject<float>(origin), graphics_(graphics_facade), color_(color)
		{
			object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::bullet);
			translate(object_matrix_, origin);
		}

		void update()
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

			speed_ += 0.1f;

			const auto direction = Vector3D<float>{ speed_, 0.f, 0.f };

			object_matrix_ = translate(object_matrix_, direction);

			graphics_.draw_matrix(object_matrix_, color_);
		}

	private:
		graphics::GraphicsFacade graphics_;
		graphics::Color color_;

		float speed_{ 0.1f };
	};
}

#endif