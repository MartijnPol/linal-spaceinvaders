#ifndef GAME_SPACE_SHIP_H
#define GAME_SPACE_SHIP_H

#include "GraphicsFacade.h"
#include "GameObject.h"
#include "Bullet.h"

struct Line3D;

namespace game
{
	class SpaceShip : public GameObject<float>
	{
	public:
		explicit SpaceShip(graphics::GraphicsFacade& graphics_facade, graphics::Color color, Vector3D<float> origin);
		void update();
		void fire_bullet();
		void handle(Line3D translated, float degrees);

		bool pitch_up{ false };
		bool pitch_down{ false };
		bool roll_left{ false };
		bool roll_right{ false };
		bool yaw_left{ false };
		bool yaw_right{ false };

		float pitch_degrees{ 0.0f };
		float roll_degrees{ 0.0f };
		float yaw_degrees{ 0.0f };

	private:
		float speed_{ 0.5f };
		std::unique_ptr<std::vector<Bullet>> bullets_;
		graphics::GraphicsFacade graphics_;
		graphics::Color color_;

		void reset();
		void roll();
		void pitch();
		void yaw();
	};
}

#endif
