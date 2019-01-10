#include "GraphicsFacade.h"
#include "Matrix.h"

namespace graphics
{
	GraphicsFacade::GraphicsFacade(const int width, const int height, const int spacing) : main_window_(nullptr), renderer_(nullptr)
	{
		this->width_ = width;
		this->height_ = height;
		this->spacing_ = spacing;

		init();
	}

	GraphicsFacade::~GraphicsFacade() = default;

	bool GraphicsFacade::init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			this->main_window_ = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_ * spacing_, height_ * spacing_, SDL_WINDOW_SHOWN);
			this->renderer_ = SDL_CreateRenderer(main_window_, -1, 0);
			return true;
		}

		return false;
	}

	void GraphicsFacade::draw_text(std::string& message, Point& location) const
	{
		std::cout << "DRAW_TEXT IS NOT IMPLEMENTED" << "\n";
	}

	void GraphicsFacade::draw_coordinate_system() const
	{
		SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
		SDL_RenderClear(renderer_);
		SDL_SetRenderDrawColor(renderer_, 211, 211, 211, 255);

		for (auto x = 0; x < width_; ++x)
		{
			for (auto y = 0; y < height_; ++y)
			{
				SDL_Rect rect{ x * spacing_, y * spacing_, spacing_, spacing_ };
				SDL_RenderDrawRect(renderer_, &rect);
			}
		}

		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer_, width_ * spacing_ / 2, height_ * spacing_, width_ * spacing_ / 2, 0);
		SDL_RenderDrawLine(renderer_, width_ * spacing_, height_ * spacing_ / 2, 0, height_ * spacing_ / 2);

		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::draw_vector(const Vector2D vector, preset_color preset_color) const
	{
		auto center_of_system = Point(width_ / 2.0f, height_ / 2.0f);
		const auto origin = center_of_system.add(vector.origin);

		const auto x = (origin.x + vector.x) * spacing_;
		const auto y = (origin.y + vector.y) * spacing_;

		const auto color = preset_colors_[static_cast<int>(preset_color)];
		SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, 255);
		SDL_RenderDrawLine(renderer_, origin.x * spacing_, origin.y * spacing_, x, y);
		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::draw_outline(const std::vector<std::unique_ptr<Vector2D>>& vectors, preset_color preset_color) const
	{
		// NOT WORKING
		for (auto&& vector : vectors)
		{
			auto center_of_system = Point(width_ / 2.0f, height_ / 2.0f);
			const auto origin = center_of_system.add(vector->origin);

			const auto x = (origin.x + vector->x) * spacing_;
			const auto y = (origin.y + vector->y) * spacing_;

			const auto color = preset_colors_[static_cast<int>(preset_color)];
			SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, 255);
			SDL_RenderDrawLine(renderer_, origin.x * spacing_, origin.y * spacing_, x, y);

			SDL_RenderPresent(renderer_);
		}
	}

	void GraphicsFacade::draw_rectangle(SDL_Rect &rectangle, preset_color preset_color) const
	{
		auto new_rectangle = SDL_Rect{ rectangle.x, rectangle.y, rectangle.w, rectangle.h };

		auto center_of_system = Point(width_ / 2.0f, height_ / 2.0f);
		const auto origin = center_of_system.add({ static_cast<float>(new_rectangle.x), static_cast<float>(new_rectangle.y) });

		new_rectangle.x = origin.x * spacing_;
		new_rectangle.y = origin.y * spacing_;

		const auto color = preset_colors_[static_cast<int>(preset_color)];
		SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, 255);
		SDL_RenderDrawRect(renderer_, &new_rectangle);
		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::draw_line(Point& start, Point& end, preset_color preset_color) const
	{
		const auto color = preset_colors_[static_cast<int>(preset_color)];
		SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, 255);

		const auto starting_x = start.x * spacing_;
		const auto starting_y = start.y * spacing_;

		const auto end_x = end.x * spacing_;
		const auto end_y = end.y * spacing_;

		SDL_RenderDrawLine(renderer_, starting_x, starting_y, end_x, end_y);
		SDL_RenderPresent(renderer_);
	}

	void GraphicsFacade::clear() const
	{
		SDL_RenderClear(renderer_);
	}
}
