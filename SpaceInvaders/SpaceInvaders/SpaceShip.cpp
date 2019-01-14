#include "SpaceShip.h"
#include "ShapeFactory.h"

using namespace utils;

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, const Vector3D<float> origin)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::spaceship);
	}

	void SpaceShip::update()
	{
		object_matrix_ = rotate(object_matrix_, { dive(), turn(), roll() });
		graphics_.draw_matrix(object_matrix_, color_);
	}
}

