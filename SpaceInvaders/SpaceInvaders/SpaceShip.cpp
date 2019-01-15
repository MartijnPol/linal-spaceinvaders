#include "SpaceShip.h"
#include "ShapeFactory.h"

using namespace utils;

namespace game
{
	SpaceShip::SpaceShip(graphics::GraphicsFacade & graphics_facade, const graphics::Color color, Vector3D<float> origin)
		: GameObject<float>(origin), graphics_(graphics_facade), color_(color)
	{
		object_matrix_ = ShapeFactory::get_shape<float>(ShapeFactory::spaceship, origin);
		object_matrix_ = translate(object_matrix_, origin);
		location_ = origin;
	}

	void SpaceShip::update()
	{
		auto result = translate(object_matrix_, Vector3D<float>{ move(), 0.0f, 0.0f });
		//const auto rotation_vector = Vector3D<float>{ dive(), turn(), roll() };
		//const auto rotation_matrix = rotate(rotation_vector);
		//auto result = rotation_matrix * object_matrix_;
		graphics_.draw_matrix(result, color_);
	}
}

