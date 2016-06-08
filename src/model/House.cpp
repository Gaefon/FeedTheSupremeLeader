#include <model/House.h>
#include <Constants.hpp>
#include <utilities/RessourceManager.h>
#include <helper/ColorHelper.h>

using namespace std;

House::House(MainWindow *prt) : Building(prt)
{
	Building::setName(HOUSE_NAME);
	Building::setHeight(3);
	Building::setWidth(3);
	m_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::House));
	draw_surface.x = 0;
	draw_surface.y = 0;
	draw_surface.w = 3 * DEFAULT_WINDOWS_TILE;
	draw_surface.h = 3 * DEFAULT_WINDOWS_TILE;

	ColorHelper::parseColor(&m_map_color, COLOR_HOUSE_MINIMAP);
}

House::~House()
{
	SDL_DestroyTexture(m_texture);
}


void House::drawBuilding(int rel_x, int rel_y)
{
	draw_surface.x = (getPosX() * DEFAULT_WINDOWS_TILE) + rel_x;
	draw_surface.y = (getPosY() * DEFAULT_WINDOWS_TILE) + rel_y;
	SDL_RenderCopy(getParent()->getRenderer(), m_texture, NULL, &draw_surface);
}

SDL_Color *House::getMinimapBuidingColor()
{
	return &m_map_color;
}

bool House::onVillageUpdateRequest(Village *village)
{
	(void) village;
    return true;
}
