#include "GraphicsFacade.h"
#include "Matrix.h"

namespace graphics
{
	GraphicsFacade::GraphicsFacade(const int width, const int height, const int spacing) : _main_window(nullptr), _renderer(nullptr)
	{
		this->_width = width;
		this->_height = height;
		this->_spacing = spacing;
	}

	GraphicsFacade::~GraphicsFacade() = default;

	bool GraphicsFacade::init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			this->_main_window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width * _spacing, _height * _spacing, SDL_WINDOW_SHOWN);
			this->_renderer = SDL_CreateRenderer(_main_window, -1, 0);
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
		SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
		SDL_RenderClear(_renderer);
		SDL_SetRenderDrawColor(_renderer, 211, 211, 211, 255);

		for (auto x = 0; x < _width; ++x)
		{
			for (auto y = 0; y < _height; ++y)
			{
				SDL_Rect rect{ x * _spacing, y * _spacing, _spacing, _spacing };
				SDL_RenderDrawRect(_renderer, &rect);
			}
		}

		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(_renderer, _width * _spacing / 2, _height * _spacing, _width * _spacing / 2, 0);
		SDL_RenderDrawLine(_renderer, _width * _spacing, _height * _spacing / 2, 0, _height * _spacing / 2);

		SDL_RenderPresent(_renderer);
	}

	void GraphicsFacade::draw_vector(const Vector2D vector, preset_color preset_color) const
	{
		auto center_of_system = Point(_width / 2.0f, _height / 2.0f);
		const auto origin = center_of_system.add(vector.origin);

		const auto x = (origin.x + vector.x) * _spacing;
		const auto y = (origin.y + vector.y) * _spacing;

		const auto color = _preset_colors[static_cast<int>(preset_color)];
		SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, 255);
		SDL_RenderDrawLine(_renderer, origin.x * _spacing, origin.y * _spacing, x, y);
		SDL_RenderPresent(_renderer);
	}

	void GraphicsFacade::draw_outline(const std::vector<std::unique_ptr<Vector2D>>& vectors, preset_color preset_color) const
	{
		// NOT WORKING
		for (auto&& vector : vectors)
		{
			auto center_of_system = Point(_width / 2.0f, _height / 2.0f);
			const auto origin = center_of_system.add(vector->origin);

			const auto x = (origin.x + vector->x) * _spacing;
			const auto y = (origin.y + vector->y) * _spacing;

			const auto color = _preset_colors[static_cast<int>(preset_color)];
			SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, 255);
			SDL_RenderDrawLine(_renderer, origin.x * _spacing, origin.y * _spacing, x, y);

			SDL_RenderPresent(_renderer);
		}
	}

	void GraphicsFacade::draw_rectangle(SDL_Rect &rectangle, preset_color preset_color) const
	{
		auto new_rectangle = SDL_Rect{ rectangle.x, rectangle.y, rectangle.w, rectangle.h };

		auto center_of_system = Point(_width / 2.0f, _height / 2.0f);
		const auto origin = center_of_system.add({ static_cast<float>(new_rectangle.x), static_cast<float>(new_rectangle.y) });

		new_rectangle.x = origin.x * _spacing;
		new_rectangle.y = origin.y * _spacing;

		const auto color = _preset_colors[static_cast<int>(preset_color)];
		SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, 255);
		SDL_RenderDrawRect(_renderer, &new_rectangle);
		SDL_RenderPresent(_renderer);
	}

	void GraphicsFacade::draw_line(Point& start, Point& end, preset_color preset_color) const
	{
		const auto color = _preset_colors[static_cast<int>(preset_color)];
		SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, 255);

		const auto starting_x = start.x * _spacing;
		const auto starting_y = start.y * _spacing;

		const auto end_x = end.x * _spacing;
		const auto end_y = end.y * _spacing;

		SDL_RenderDrawLine(_renderer, starting_x, starting_y, end_x, end_y);
		SDL_RenderPresent(_renderer);
	}

	void GraphicsFacade::clear() const
	{
		SDL_RenderClear(_renderer);
	}
}
