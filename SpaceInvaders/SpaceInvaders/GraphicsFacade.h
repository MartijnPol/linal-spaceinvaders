#ifndef GRAPHICS_GRAPHICS_FACADE_H
#define GRAPHICS_GRAPHICS_FACADE_H

#include <SDL.h>
#include <vector>
#include "Matrix.h"
#include "Vector2D.h"

using namespace math;

namespace graphics
{
	struct Color
	{
		int red;
		int green;
		int blue;

		Color() = default;
		Color(const int r, const int g, const int b) : red(r), green(g), blue(b) { }
	};

	class GraphicsFacade
	{
	public:

		enum class preset_color { red, green, blue, white };

		GraphicsFacade(int width, int height, int spacing);
		~GraphicsFacade();

		void draw_vector(Vector2D vector, preset_color preset_color) const;
		void draw_outline(const std::vector<std::unique_ptr<Vector2D>> &vectors, const preset_color preset_color) const;
		void draw_rectangle(SDL_Rect &rectangle, preset_color preset_color) const;
		void draw_line(Point &start, Point &end, preset_color preset_color) const;
		void clear() const;

		template<typename T>
		void draw_matrix(Matrix<T> &matrix, const preset_color preset_color) const
		{
			for (auto i = 0; i < matrix.columns; ++i) {

				Point start{ 0,0 };
				Point end{ 0,0 };

				if (i == matrix.columns - 1) {
					start.x = matrix.at(0, i);
					start.y = matrix.at(1, i);

					end.x = matrix.at(0, 0);
					end.y = matrix.at(1, 0);
				}
				else {
					start.x = matrix.at(0, i);
					start.y = matrix.at(1, i);

					end.x = matrix.at(0, i + 1);
					end.y = matrix.at(1, i + 1);
				}

				start = Point(width_ / 2.0f, height_ / 2.0f).add(start);
				end = Point(width_ / 2.0f, height_ / 2.0f).add(end);

				draw_line(start, end, preset_color);
			}
		}

	private:
		int width_, height_, spacing_;
		SDL_Window *main_window_;
		SDL_Renderer *renderer_;
		Color preset_colors_[4] = { Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255), Color(255,255,255) };
		
		bool init();
		void draw_text(std::string &message, Point &location) const;
	};
}

#endif