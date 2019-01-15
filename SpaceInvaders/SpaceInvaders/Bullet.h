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
			original_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::bullet);
			translate(original_matrix_, origin);
		}

		void update()
		{
			draw_matrix_ = original_matrix_;

			// Get points in shape
			const auto a = original_matrix_.get_point_vector(0);
			const auto d = original_matrix_.get_point_vector(3);
			const auto h = original_matrix_.get_point_vector(7);

			auto ad = Line3D{ a, d };
			const auto hd = Line3D{ h, d };

			auto result = ad.cross_product(hd);

			const auto middle_vector = original_matrix_.get_middle_vector();
			const auto translated = result.translate(middle_vector);

			speed_ += 1.0f;

			const auto direction = Vector3D<float>{ speed_, 0.f, 0.f };
			origin_ += direction;

			draw_matrix_ = translate(draw_matrix_, origin_);

			graphics_.draw_matrix(draw_matrix_, color_);
		}

	private:
		graphics::GraphicsFacade graphics_;
		graphics::Color color_;

		float speed_{ 0.1f };
	};
}

#endif