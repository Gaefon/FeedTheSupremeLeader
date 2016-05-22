#ifndef COLOR_HELPER_H
#define COLOR_HELPER_H

#include <SDL.h>

class ColorHelper
{
	public:
		static void parseColor(SDL_Color *color, int hex);
};

#endif