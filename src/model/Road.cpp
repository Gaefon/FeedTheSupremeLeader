#include <model/Road.h>
#include <Constants.hpp>
#include <utilities/RessourceManager.h>
#include <helper/ColorHelper.h>

using namespace std;

Road::Road(MainWindow *prt) : Building(prt)
{
	Building::setName(ROAD_NAME);
	Building::setHeight(1);
	Building::setWidth(1);
	m_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::Road));
	draw_surface.x = 0;
	draw_surface.y = 0;
	draw_surface.w = DEFAULT_WINDOWS_TILE;
	draw_surface.h = DEFAULT_WINDOWS_TILE;

	ColorHelper::parseColor(&m_map_color, COLOR_ROAD_MINIMAP);
}

Road::~Road()
{
	SDL_DestroyTexture(m_texture);
}


void Road::drawBuilding(int rel_x, int rel_y)
{
	draw_surface.x = (getPosX() * DEFAULT_WINDOWS_TILE) + rel_x;
	draw_surface.y = (getPosY() * DEFAULT_WINDOWS_TILE) + rel_y;
	SDL_RenderCopy(getParent()->getRenderer(), m_texture, NULL, &draw_surface);
}

bool Road::isDraggable()
{
	return true;
}

bool Road::onVillageUpdateRequest(Village *village)
{
	(void) village;
    return true;
}

SDL_Color *Road::getMinimapBuidingColor()
{
	return &m_map_color;
}
