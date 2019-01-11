#include "SpaceShip.h"

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::GraphicsFacade::preset_color color) : graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = Matrix<float>(4, 10, { 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 1.0f, 2.0f, 0.0f, 2.0f, 1.0f,
												2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f,
												0.0f, 2.0f, 0.0f, 1.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
												0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	}

	void SpaceShip::update()
	{
		graphics_.draw_matrix(object_matrix_, color_);
	}

	void SpaceShip::rotate(const Vector3D<float> vector)
	{
		object_matrix_ = math::rotate(object_matrix_, vector);
	}
}

