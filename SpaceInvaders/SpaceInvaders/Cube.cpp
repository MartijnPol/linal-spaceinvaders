#include "Cube.h"

namespace game
{
	Cube::Cube(graphics::GraphicsFacade & graphics_facade, const graphics::GraphicsFacade::preset_color color) : graphics_(graphics_facade), color_(color)
	{
		const auto s = 5.0f;
		object_matrix_ = Matrix<float>(4, 8, { 0, 0, s, s, 0, 0, s, s,
											   0, s, s, 0, 0, s, s, 0,
											   0, 0, 0, 0, s, s, s, s,
											   0, 0, 0, 0, 0, 0, 0, 0 });
	}

	void Cube::update()
	{
		object_matrix_ = rotate(object_matrix_, { {0,0}, turn(), dive(), roll() });
		graphics_.draw_matrix(object_matrix_, color_);
	}
}
