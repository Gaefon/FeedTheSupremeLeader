#include <list>
#include <math.h>

#include <uiclass/Minimap.h>
#include <helper/ColorHelper.h>
#include <helper/RectHelper.h>
#include <Constants.hpp>

using namespace std;

Minimap::Minimap(MainWindow *parent, int pos_x, int pos_y, Map *map): Widget(parent)
{
	m_map = map;

	m_draw_rect.x = pos_x;
	m_draw_rect.y = pos_y;
	m_draw_rect.w = m_map->getWidth();
	m_draw_rect.h = m_map->getHeight();
	ColorHelper::parseColor(&m_default_color, COLOR_GREEN_MAP);
	m_map_pos_rect.x = 0;
	m_map_pos_rect.y = 0;
	m_map_pos_rect.w = roundf(getParent()->getWidth() / DEFAULT_WINDOWS_TILE);
	m_map_pos_rect.h = roundf((getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT) / DEFAULT_WINDOWS_TILE);

	m_is_clicked = false;
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

void Minimap::setPosition(int x, int y)
{
	m_draw_rect.x = x;
	m_draw_rect.y = y;
}

bool Minimap::onSdlEventReceived(SDL_Event event)
{
	bool rtn_val = false;
	bool is_over = RectHelper::isInRect(&m_draw_rect, event.button.x, event.button.y);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (is_over)
			{
				m_is_clicked = true;
				m_map->setTileMapPos(event.motion.x - m_draw_rect.x - m_map_pos_rect.w / 2, event.motion.y - m_draw_rect.y - m_map_pos_rect.h / 2);
				rtn_val = true;
			}
			break;
		case SDL_MOUSEMOTION:
			if (is_over && m_is_clicked)
			{
				m_map->setTileMapPos(event.motion.x - m_draw_rect.x - m_map_pos_rect.w / 2, event.motion.y - m_draw_rect.y - m_map_pos_rect.h / 2);
				rtn_val = true;
			}
			else
				m_is_clicked = false;
			break;
		case SDL_MOUSEBUTTONUP:
			m_is_clicked = false;
			break;
	}
	return rtn_val;
}

void Minimap::draw()
{
	list<Building *> *blds = m_map->getBuildings();
	SDL_Rect tmp;
	SDL_Color *tmp_color;
	SDL_SetRenderDrawColor(getParent()->getRenderer(), m_default_color.r, m_default_color.g, m_default_color.b, m_default_color.a);
	SDL_RenderFillRect(getParent()->getRenderer(), &m_draw_rect);

	// draw map rectangle on the minimap
	m_map_pos_rect.x = m_draw_rect.x - m_map->getTilePosX();
	m_map_pos_rect.y = m_draw_rect.y - m_map->getTilePosY();
	SDL_SetRenderDrawColor(getParent()->getRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(getParent()->getRenderer(), &m_map_pos_rect);

	for (list<Building *>::iterator it = blds->begin(); it != blds->end(); ++it)
	{
		tmp.x = (*it)->getPosX() + m_draw_rect.x;
		tmp.y = (*it)->getPosY() + m_draw_rect.y;
		tmp.w = (*it)->getWidth();
		tmp.h = (*it)->getHeight();
		tmp_color = (*it)->getMinimapBuidingColor();
		SDL_SetRenderDrawColor(getParent()->getRenderer(), tmp_color->r, tmp_color->g, tmp_color->b, tmp_color->a);
		SDL_RenderFillRect(getParent()->getRenderer(), &tmp);
	}
}
