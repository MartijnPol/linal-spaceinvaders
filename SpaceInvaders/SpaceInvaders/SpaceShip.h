#ifndef GAME_SPACE_SHIP_H
#define GAME_SPACE_SHIP_H

#include "GraphicsFacade.h"
#include "GameObject.h"

namespace game
{
	class SpaceShip : public GameObject<float>
	{
	public:
		explicit SpaceShip(graphics::GraphicsFacade& graphics_facade, graphics::Color color, Vector3D<float> origin);
		void update();

	private:
		graphics::GraphicsFacade graphics_;
		graphics::Color color_;
		Vector3D<float> location_;
	};
}

#endif
