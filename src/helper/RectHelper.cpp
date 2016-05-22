#include <helper/RectHelper.h>

bool RectHelper::isInRect(SDL_Rect *rect, int x, int y)
{
	if (x >= rect->x && y >= rect->y && x < (rect->x + rect->w) && y < (rect->w + rect->h))
		return true;
	return false;
}