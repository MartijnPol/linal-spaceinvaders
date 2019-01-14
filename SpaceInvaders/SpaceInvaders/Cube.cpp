#include "Cube.h"
#include "ShapeFactory.h"

using namespace utils;

namespace game
{
	Cube::Cube(graphics::GraphicsFacade & graphics_facade, const graphics::Color color) : graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::target);
	}

	void Cube::update()
	{
		object_matrix_ = rotate(object_matrix_, { {0,0}, turn(), dive(), roll() });
		graphics_.draw_matrix(object_matrix_, color_);
	}
}
