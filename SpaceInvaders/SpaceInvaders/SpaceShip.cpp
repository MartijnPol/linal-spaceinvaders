#include "SpaceShip.h"
#include "ShapeFactory.h"

using namespace utils;

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, const Vector3D<float> origin)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::spaceship, origin);
	}

	void SpaceShip::update()
	{
		const auto rotation_vector = Vector3D<float>{ dive(), turn(), roll() };
		const auto rotation_matrix = rotate(rotation_vector);
		auto result = rotation_matrix * object_matrix_;
		graphics_.draw_matrix(result, color_);
		reset();
	}
}

