#ifndef GAME_GRAPHICS_GRAPHICS_FACADE_H
#define GAME_GRAPHICS_GRAPHICS_FACADE_H

#include <SDL.h>
#include <vector>
#include "Matrix.h"
#include "Vector2D.h"
#include "Color.h"

using namespace math;

namespace graphics
{
	struct Color;

	class GraphicsFacade
	{
	public:

		GraphicsFacade(int width, int height, int spacing);
		~GraphicsFacade();

		void draw_vector(Vector2D<float> vector, Color color) const;
		void draw_outline(const std::vector<std::unique_ptr<Vector2D<float>>> &vectors, Color color) const;
		void draw_rectangle(SDL_Rect &rectangle, Color color) const;
		void draw_line(Vector2D<float> &start, Vector2D<float> &end, Color color) const;
		void clear() const;

		template<typename T>
		void draw_matrix(Matrix<T> &matrix, const Color color) const
		{
			for (auto i = 0; i < matrix.columns; ++i) {

				Vector2D<T> start{ 0.0f, 0.0f };
				Vector2D<T> end{ 0.0f, 0.0f };

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

				start = Vector2D<T>(width_ / 2.0f, height_ / 2.0f) + start;
				end = Vector2D<T>(width_ / 2.0f, height_ / 2.0f) + end;

				draw_line(start, end, color);
			}
		}

	private:
		int width_, height_, spacing_;
		SDL_Window *main_window_;
		SDL_Renderer *renderer_;

		bool init();
	};
}

#endif