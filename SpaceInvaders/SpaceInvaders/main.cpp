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

	auto space_ship = game::SpaceShip{ graphics, GraphicsFacade::preset_color::white };
	auto cube = game::Cube{ graphics, GraphicsFacade::preset_color::red };

	//auto x = 10.0f;
	//auto y = -10.0f;
	//auto z = 30.0f;
	//auto size = 5.0f;
	//auto x_size = x + size;
	//auto y_size = y + size;
	//auto z_size = z + size;

	/*auto target = Matrix<float>(4, 8, { x, y, z, x, y_size, z, x_size, y_size,
										z, x_size, y, z, x, y, z_size, x,
										y_size, z_size, x_size, y_size, z_size, x_size, y, z_size,
										0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });*/

	Vector3D<float> translate_vector({ 2, 2 }, 1.0f, 1.0f, 1.0f);

	const auto max_scale_factor = 0.2f;
	auto scale_factor = 0.0f;
	auto reversed = false;

	auto speed = 0.1f;

	SDL_Event event;
	while (is_running)
	{
		timer.update();
		if (timer.delta_time() >= 1.0f / 60.0f)
		{
			graphics.clear();

			//space_ship.update();
			cube.update();

			////Vector3D<float> scale_vector({ 2, 2 }, scale_factor, scale_factor, scale_factor);

			//translate_vector += Vector3D<float>({ 2,2 }, 5.0f, 3.0f, 1.0f);

			//auto rotated_rocket = rotate(rocket, translate_vector);
			//auto translated_rocket = translate(rotated_rocket, translate_vector);

			//graphics.draw_matrix(translated_rocket, GraphicsFacade::preset_color::blue);

			/*auto rotated_target = rotate(target, translate_vector);
			auto scaled_target = scale(rotated_target, scale_vector);
			graphics.draw_matrix(scaled_target, GraphicsFacade::preset_color::red);*/

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
					cube.increase_dive(2.0f);
					break;

				case SDLK_a:
					space_ship.decrease_turn(2.0f);
					cube.decrease_turn(2.0f);
					break;

				case SDLK_s:
					space_ship.decrease_dive(2.0f);
					cube.decrease_dive(2.0f);
					break;

				case SDLK_d:
					space_ship.increase_turn(2.0f);
					cube.increase_turn(2.0f);
					break;

				case SDLK_q:
					space_ship.decrease_roll(2.0f);
					cube.decrease_roll(2.0f);
					break;

				case SDLK_e:
					space_ship.increase_roll(2.0f);
					cube.increase_roll(2.0f);
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

			if (scale_factor <= max_scale_factor && !reversed)
			{
				scale_factor += 0.01f;
				if (scale_factor >= max_scale_factor) reversed = true;
			}
			else if (reversed)
			{
				scale_factor -= 0.01f;
				if (scale_factor <= 0.0f) reversed = false;
			}

			timer.reset();
		}
	}

	SDL_Quit();
	return 0;
}