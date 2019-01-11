#ifndef GAME_CUBE_H
#define GAME_CUBE_H

#include "GraphicsFacade.h"
#include "GameObject.h"

namespace game
{
	class Cube : public GameObject<float>
	{
	public:
		explicit Cube(graphics::GraphicsFacade& graphics_facade, graphics::GraphicsFacade::preset_color color);
		void update();

	private:
		graphics::GraphicsFacade graphics_;
		graphics::GraphicsFacade::preset_color color_;
	};
}

#endif
