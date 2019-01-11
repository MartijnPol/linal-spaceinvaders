#include <iostream>

#include "Point.h"
#include "GraphicsFacade.h"
#include "Matrix.h"
#include "SDL.h"
#include "ShapeFactory.h"
#include "TimerFacade.h"
#include <array>

using namespace std;
using namespace math;
using namespace graphics;
using namespace utils;

int main(int argc, char * argv[])
{
	//DO NOT DELETE THIS LINE: IT'S INTENDED TO DETECT MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto is_running = true;

	const auto spacing = 25;
	const auto width = 30;
	const auto height = 20;

	auto timer = TimerFacade{};
	auto graphics = GraphicsFacade{ width,height,spacing };

	auto rocket = Matrix<float>(4, 10, { 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 1.0f, 2.0f, 0.0f, 2.0f, 1.0f,
										 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f,
										 0.0f, 2.0f, 0.0f, 1.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
										 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
	);

	auto target = Matrix<float>(4, 4, { 0.0f, 0.0f, 5.0f, 5.0f,
										0.0f, 5.0f, 5.0f, 0.0f,
										1.0f, 1.0f, 1.0f, 1.0f,
										0.0f, 0.0f, 0.0f, 0.0f });

	Vector3D<float> translate_vector({ 2, 2 }, 1.0f, 1.0f, 1.0f);

	const auto max_scale_factor = 0.5f;
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
			graphics.draw_coordinate_system();

			Vector3D<float> scale_vector({ 2, 2 }, scale_factor, scale_factor, scale_factor);

			translate_vector += Vector3D<float>({ 2,2 }, 5.0f, 3.0f, 1.0f);

			auto rotated_rocket = rotate(rocket, translate_vector);
			auto translated_rocket = translate(rotated_rocket, translate_vector);

			graphics.draw_matrix(translated_rocket, GraphicsFacade::preset_color::blue);

			auto rotated_target = rotate(target, translate_vector);
			auto scaled_target = scale(rotated_target, scale_vector);
			graphics.draw_matrix(scaled_target, GraphicsFacade::preset_color::red);

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
				case SDLK_a:
					translate_vector.z -= speed;
					break;

				case SDLK_d:
					translate_vector.z += speed;
					break;

				case SDLK_w:
					translate_vector.y += speed;
					break;

				case SDLK_s:
					translate_vector.y -= speed;
					break;

				case SDLK_LSHIFT:
					speed += 0.01f;
					break;

				case SDLK_RSHIFT:
					speed -= 0.01f;
					break;

				case SDLK_q:
					rotate(translated_rocket, translate_vector);
					break;

				case SDLK_e:
					rotate(translated_rocket, translate_vector);
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