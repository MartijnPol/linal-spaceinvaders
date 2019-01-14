#include "GraphicsFacade.h"

namespace graphics
{
	GraphicsFacade::GraphicsFacade(const int width, const int height) : main_window_(nullptr), renderer_(nullptr)
	{
		this->width_ = width;
		this->height_ = height;

		init();
	}

	GraphicsFacade::~GraphicsFacade() = default;

	bool GraphicsFacade::init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			this->main_window_ = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
			this->renderer_ = SDL_CreateRenderer(main_window_, -1, 0);
			return true;
		}

		return false;
	}

	void GraphicsFacade::draw_vector(const Vector2D<float> vector, const Color color) const
	{
		const auto center_of_system = Vector2D<float>(width_ / 2.0f, height_ / 2.0f);
		const auto origin = center_of_system + vector;

		const auto x = origin.x + vector.x;
		const auto y = origin.y + vector.y;

		SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, 255);
		SDL_RenderDrawLine(renderer_, origin.x, origin.y, x, y);
		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::draw_line(Vector2D<float>& start, Vector2D<float>& end, const Color color) const
	{
		SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, 255);

		const auto starting_x = start.x;
		const auto starting_y = start.y;

		const auto end_x = end.x;
		const auto end_y = end.y;

		SDL_RenderDrawLine(renderer_, starting_x, starting_y, end_x, end_y);
		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::draw_line(Vector3D<float>& start, Vector3D<float>& end, const Color color) const
	{
		SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, 255);

		start += Vector3D<float>(width_ / 2.0f, height_ / 2.0f, 0.0f);
		end += Vector3D<float>(width_ / 2.0f, height_ / 2.0f, 0.0f);

		const auto starting_x = start.x;
		const auto starting_y = start.y;

		const auto end_x = end.x;
		const auto end_y = end.y;

		SDL_RenderDrawLine(renderer_, starting_x, starting_y, end_x, end_y);
		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::draw_axes() const
	{
		SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 100);
		
		SDL_RenderDrawLine(renderer_, 0, height_ / 2, width_, height_ / 2);
		SDL_RenderDrawLine(renderer_, width_ / 2, 0, width_ / 2, height_);
		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::clear() const
	{
		SDL_RenderClear(renderer_);
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
		SDL_RenderClear(renderer_);

		//draw_axes();
	}
}
