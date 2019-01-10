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
	const auto degrees = 1.0f;

	auto timer = TimerFacade{};
	auto graphics = GraphicsFacade{ width,height,spacing };

	auto rocket = Matrix<float>(3, 4, { 0, 0, 5, 5,
										0, 5, 5, 0,
										1, 1, 1, 1 });

	auto target = Matrix<float>(3, 4, { 0, 0, 5, 5,
										0, 5, 5, 0,
										1, 1, 1, 1 });

	const auto max_scale_factor = 0.5f;
	auto scale_factor = 0.0f;
	auto reversed = false;

	SDL_Event event;
	while (is_running)
	{
		timer.update();
		if (timer.delta_time() >= 1.0f / 60.0f)
		{
			graphics.clear();
			graphics.draw_coordinate_system();

			auto rotated_rocket = rotate(rocket, degrees, 2.0f, 2.0f);
			graphics.draw_matrix(rotated_rocket, GraphicsFacade::preset_color::blue);

			auto scaled_target = scale(target, scale_factor, scale_factor);
			graphics.draw_matrix(scaled_target, GraphicsFacade::preset_color::red);

			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT)
			{
				is_running = false;
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