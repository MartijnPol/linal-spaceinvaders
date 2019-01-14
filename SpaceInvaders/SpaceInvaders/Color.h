#ifndef GAME_GRAPHICS_COLOR_H
#define GAME_GRAPHICS_COLOR_H

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

	namespace colors
	{
		static const Color WHITE = { 255, 255, 255 };
		static const Color GRAY = { 180, 180, 180 };
		static const Color BLACK = { 0, 0, 0 };
		static const Color RED = { 255, 0, 0 };
		static const Color GREEN = { 0, 255, 0 };
		static const Color BLUE = { 0, 0, 255 };
	}
}

#endif