#ifndef GAME_SPACE_SHIP_H
#define GAME_SPACE_SHIP_H

#include "GraphicsFacade.h"
#include "GameObject.h"
#include "Bullet.h"

namespace game
{
	class SpaceShip : public GameObject<float>
	{
	public:
		explicit SpaceShip(graphics::GraphicsFacade& graphics_facade, graphics::Color color, Vector3D<float> origin);
		void update();
		void fire_bullet();

	private:
		std::unique_ptr<std::vector<Bullet>> bullets_;
		graphics::GraphicsFacade graphics_;
		graphics::Color color_;
		Vector3D<float> location_;
		float degrees_{ 0.0f };

	};
}

#endif
