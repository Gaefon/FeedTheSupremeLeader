#include <iostream>
#include <model/Farm.hpp>
#include <Constants.hpp>
#include <utilities/RessourceManager.h>
#include <helper/ColorHelper.h>
#include <model/Village.h>

using namespace std;

Farm::Farm(MainWindow *prt) : Building(prt)
{
	Building::setName(FARM_NAME);
	Building::setHeight(5);
	Building::setWidth(5);
	m_production_rate = 1;
	m_max_workers = 10;
	m_nb_workers = 0;
	m_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::Farm));
	draw_surface.x = 0;
	draw_surface.y = 0;
	draw_surface.w = 5 * DEFAULT_WINDOWS_TILE;
	draw_surface.h = 5 * DEFAULT_WINDOWS_TILE;

	ColorHelper::parseColor(&m_map_color, COLOR_FARM_MINIMAP);
}

Farm::~Farm()
{
	SDL_DestroyTexture(m_texture);
}


void Farm::drawBuilding(int rel_x, int rel_y)
{
	draw_surface.x = (getPosX() * DEFAULT_WINDOWS_TILE) + rel_x;
	draw_surface.y = (getPosY() * DEFAULT_WINDOWS_TILE) + rel_y;
	SDL_RenderCopy(getParent()->getRenderer(), m_texture, NULL, &draw_surface);
}

SDL_Color *Farm::getMinimapBuidingColor()
{
	return &m_map_color;
}

int Farm::getProductionRate()
{
    return m_production_rate;
}

void Farm::setProductionRate(int production)
{
    m_production_rate = production;
}

bool Farm::onVillageUpdateRequest(Village *village)
{
	village->setFood(village->getFood() + (getProductionRate() * m_nb_workers));
	village->setWorkersCapacity(village->getWorkersCapacity() + m_max_workers);
    return true;
}

void Farm::setMaxWorkers(unsigned int pop)
{
	m_max_workers = pop;
}

unsigned int Farm::getMaxWorkers()
{
	return m_max_workers;
}

void Farm::setWorkers(unsigned int pop)
{
	m_nb_workers = pop;
}

unsigned int Farm::getWorkers()
{
	return m_nb_workers;
}
