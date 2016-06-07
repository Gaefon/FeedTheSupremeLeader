#include <model/School.h>
#include <Constants.hpp>
#include <utilities/RessourceManager.h>
#include <helper/ColorHelper.h>

using namespace std;

School::School(MainWindow *prt) : Building(prt)
{
	Building::setName(SCHOOL_NAME);
	Building::setHeight(4);
	Building::setWidth(4);
	m_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::School));
	draw_surface.x = 0;
	draw_surface.y = 0;
	draw_surface.w = 4 * DEFAULT_WINDOWS_TILE;
	draw_surface.h = 4 * DEFAULT_WINDOWS_TILE;

	ColorHelper::parseColor(&m_map_color, COLOR_HOUSE_MINIMAP);
}

School::~School()
{
	SDL_DestroyTexture(m_texture);
}


void School::drawBuilding(int rel_x, int rel_y)
{
	draw_surface.x = (getPosX() * DEFAULT_WINDOWS_TILE) + rel_x;
	draw_surface.y = (getPosY() * DEFAULT_WINDOWS_TILE) + rel_y;
	SDL_RenderCopy(getParent()->getRenderer(), m_texture, NULL, &draw_surface);
}

SDL_Color *School::getMinimapBuidingColor()
{
	return &m_map_color;
}