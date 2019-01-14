#include "SpaceShip.h"
#include "ShapeFactory.h"

using namespace utils;

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::Color color) : graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::spaceship);
	}

	void SpaceShip::update()
	{
		object_matrix_ = rotate(object_matrix_, { {0,0}, turn(), dive(), roll() });
		graphics_.draw_matrix(object_matrix_, color_);
	}
}

