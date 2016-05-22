#include <helper/ColorHelper.h>

void ColorHelper::parseColor(SDL_Color *color, int hex)
{
	color->a = hex & 0x000000ff;
	color->b = (hex & 0x0000ff00) >> 8;
	color->g = (hex & 0x00ff0000) >> 16;
	color->r = (hex & 0xff000000) >> 24;
}