#ifndef GAME_SPACE_SHIP_H
#define GAME_SPACE_SHIP_H

#include "GraphicsFacade.h"

namespace game
{
	class SpaceShip
	{
	public:
		explicit SpaceShip(graphics::GraphicsFacade& graphics_facade, graphics::GraphicsFacade::preset_color color);

		void update();
		void rotate(Vector3D<float> vector);

	private:
		Matrix<float> object_matrix_;
		graphics::GraphicsFacade graphics_;
		graphics::GraphicsFacade::preset_color color_;
	};
}

#endif
