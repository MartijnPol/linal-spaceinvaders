#ifndef GAME_CUBE_H
#define GAME_CUBE_H

#include "GraphicsFacade.h"
#include "GameObject.h"
#include "Line3D.h"

namespace game
{
	class Cube : public GameObject<float>
	{
	public:
		explicit Cube(graphics::GraphicsFacade& graphics_facade, graphics::Color color, Vector3D<float> origin, bool is_target = false);
		void update();

	private:
		graphics::GraphicsFacade graphics_;
		graphics::Color color_;

		void roll();
		void pitch();
		void yaw();
		void rotate(Line3D translated);

		bool is_target_{ false };
		float max_scale_factor_{ 1.2f };
		float scale_factor_{ 1.0f };
		bool reversed_{ false };
		float pulse_speed_{ 0.03f };

		void pulse();
	};
}

#endif
