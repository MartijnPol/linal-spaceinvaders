#include "SpaceShip.h"

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::GraphicsFacade::preset_color color) : graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = Matrix<float>(4, 10, { 0.0f, 0.0f, 4.0f, 3.0f, 0.0f, 3.0f, 4.0f, 0.0f, 4.0f, 3.0f,
												4.0f, 0.0f, 0.0f, 3.0f, 0.0f, 3.0f, 0.0f, 4.0f, 0.0f, 3.0f,
												0.0f, 4.0f, 0.0f, 3.0f, 4.0f, 3.0f, 0.0f, 0.0f, 0.0f, 3.0f,
												0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	}

	void SpaceShip::update()
	{
		object_matrix_ = rotate(object_matrix_, { {0,0}, turn(), dive(), roll() });
		graphics_.draw_matrix(object_matrix_, color_);
	}
}

