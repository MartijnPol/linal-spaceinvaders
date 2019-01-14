#include <iostream>

#include "TimerFacade.h"
#include "SpaceShip.h"
#include "Cube.h"

using namespace graphics;
using namespace utils;

int main(int argc, char * argv[])
{
	//DO NOT DELETE THIS LINE: IT'S INTENDED TO DETECT MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto is_running = true;

	const auto spacing = 25;
	const auto width = 50;
	const auto height = 25;

	auto timer = TimerFacade{};
	auto graphics = GraphicsFacade{ width,height,spacing };

	auto space_ship = game::SpaceShip{ graphics, colors::WHITE, Vector3D<float>{5.0f,5.0f, -25.0f} };
	auto target = game::Cube{ graphics, colors::RED, Vector3D<float>{0.0f, 0.0f, 0.0f}, true };

	auto speed = 0.1f;

	SDL_Event event;
	while (is_running)
	{
		timer.update();
		if (timer.delta_time() >= 1.0f / 60.0f)
		{
			graphics.clear();

			space_ship.update();
			target.update();

			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				const auto key = event.key.keysym.sym;
				switch (key)
				{
				case SDLK_w:
					space_ship.increase_dive(2.0f);
					target.increase_dive(2.0f);
					break;

				case SDLK_a:
					space_ship.decrease_turn(2.0f);
					target.decrease_turn(2.0f);
					break;

				case SDLK_s:
					space_ship.decrease_dive(2.0f);
					target.decrease_dive(2.0f);
					break;

				case SDLK_d:
					space_ship.increase_turn(2.0f);
					target.increase_turn(2.0f);
					break;

				case SDLK_q:
					space_ship.decrease_roll(2.0f);
					target.decrease_roll(2.0f);
					break;

				case SDLK_e:
					space_ship.increase_roll(2.0f);
					target.increase_roll(2.0f);
					break;

				case SDLK_LSHIFT:
					speed += 0.01f;
					break;

				case SDLK_RSHIFT:
					speed -= 0.01f;
					break;

				default:
					break;
				}
			}

			timer.reset();
		}
	}

	SDL_Quit();
	return 0;
}