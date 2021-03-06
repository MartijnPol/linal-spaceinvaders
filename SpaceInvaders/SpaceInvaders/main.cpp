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

	const auto width = 960;
	const auto height = 640;

	auto timer = TimerFacade{};
	auto graphics = GraphicsFacade{ width, height };

	auto space_ship = game::SpaceShip{ graphics, colors::WHITE, Vector3D<float>{-200.0f, -200.0f, 0.0f} };
	auto target = game::Cube{ graphics, colors::RED, Vector3D<float>{200.0f, 200.0f, 0.0f}, true };
	auto second_target = game::Cube{ graphics, colors::GRAY, Vector3D<float>{0.0f, 0.0f, 0.0f}, false };

	SDL_Event event;
	while (is_running)
	{
		timer.update();
		if (timer.delta_time() >= 1.0f / 60.0f)
		{
			graphics.clear();
			space_ship.update();
			target.update();
			second_target.update();

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
					space_ship.pitch_up = true;
					break;

				case SDLK_a:
					space_ship.roll_left = true;
					break;

				case SDLK_s:
					space_ship.pitch_down = true;
					break;

				case SDLK_d:
					space_ship.roll_right = true;
					break;

				case SDLK_q:
					space_ship.yaw_left = true;
					break;

				case SDLK_e:
					space_ship.yaw_right = true;
					break;

				case SDLK_h:
					space_ship.switch_help_line();
					target.switch_help_line();
					break;

				case SDLK_1:
					graphics.current_view(GraphicsFacade::front);
					break;

				case SDLK_2:
					graphics.current_view(GraphicsFacade::top);
					break;

				case SDLK_3:
					graphics.current_view(GraphicsFacade::side);
					break;

				case SDLK_LSHIFT:
					space_ship.accelerate();
					break;

				case SDLK_SPACE:
					space_ship.fire_bullet();
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