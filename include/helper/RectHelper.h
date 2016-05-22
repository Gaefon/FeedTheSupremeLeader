#ifndef RECT_HELPER_H
#define RECT_HELPER_H

#include <SDL.h>

class RectHelper
{
	public:
		static bool isInRect(SDL_Rect *rect, int x, int y);
};

#endif