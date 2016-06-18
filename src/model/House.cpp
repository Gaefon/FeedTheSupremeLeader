#include <model/House.h>
#include <model/Village.h>
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
	m_occupancy = 0;
	m_max_occupancy = 6;
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

unsigned int House::getPrice()
{
	return PRICE_HOUSE;
}

unsigned int House::getOccupancy()
{
    return m_occupancy;
}

void House::setOccupancy(unsigned int occupancy)
{
    m_occupancy = occupancy;
}

unsigned int House::getMaxOccupancy()
{
    return m_max_occupancy;
}

void House::setMaxOccupancy(unsigned int occupancy)
{
    m_max_occupancy = occupancy;
}

bool House::onVillageUpdateRequest(Village *village)
{
    village->setHousingCapacity(village->getHousingCapacity() + getMaxOccupancy());
    return true;
}
