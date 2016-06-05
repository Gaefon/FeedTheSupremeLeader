#include <list>

#include <uiclass/Minimap.h>
#include <helper/ColorHelper.h>
#include <Constants.hpp>

using namespace std;

Minimap::Minimap(MainWindow *parent, int pos_x, int pos_y, Map *map): Widget(parent)
{
	m_map = map;

	draw_rect.x = pos_x;
	draw_rect.y = pos_y;
	draw_rect.w = m_map->getWidth();
	draw_rect.h = m_map->getHeight();
	ColorHelper::parseColor(&default_color, COLOR_GREEN_MAP);
}

Minimap::~Minimap()
{
}

int Minimap::getWidth()
{
	return m_map->getWidth();
}

int Minimap::getHeight()
{
	return m_map->getHeight();
}

void Minimap::draw()
{
	list<Building *> *blds = m_map->getBuildings();
	SDL_Rect tmp;
	SDL_SetRenderDrawColor(getParent()->getRenderer(), default_color.r, default_color.g, default_color.b, default_color.a);
	SDL_RenderFillRect(getParent()->getRenderer(), &draw_rect);

	for (list<Building *>::iterator it = blds->begin(); it != blds->end(); ++it)
	{
		tmp.x = (*it)->getPosX() + draw_rect.x;
		tmp.y = (*it)->getPosY() + draw_rect.y;
		tmp.w = (*it)->getWidth();
		tmp.h = (*it)->getHeight();

		SDL_SetRenderDrawColor(getParent()->getRenderer(), 255, 255, 255, 255);
		SDL_RenderFillRect(getParent()->getRenderer(), &tmp);
	}
}
