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

	auto timer = TimerFacade();
	auto graphics = GraphicsFacade(width, height, spacing);
	graphics.init();

	auto shape_matrix = Matrix<float>(3, 4, { 0, 0, 5, 5,
									   0, 5, 5, 0,
									   1, 1, 1, 1 });

	graphics.clear();
	//graphics.draw_coordinate_system();
	graphics.draw_matrix(shape_matrix, GraphicsFacade::preset_color::white);
	auto scale_matrix = scale(shape_matrix, 2.0f, 2.0f);
	graphics.draw_matrix(scale_matrix, GraphicsFacade::preset_color::white);

	const auto degrees = 1.0f;

	SDL_Event event;
	while (is_running)
	{
		timer.update();
		if (timer.delta_time() >= 1.0f / 60.0f)
		{
			graphics.clear();
			graphics.draw_coordinate_system();

			auto rotated_matrix = rotate(shape_matrix, degrees, 2.0f, 2.0f);
			graphics.draw_matrix(rotated_matrix, GraphicsFacade::preset_color::blue);
			
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}

			timer.reset();
		}
	}

	SDL_Quit();
	return 0;
}