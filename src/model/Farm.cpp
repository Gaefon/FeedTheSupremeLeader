#include <iostream>
#include <model/Farm.hpp>
#include <Constants.hpp>
#include <utilities/RessourceManager.h>


using namespace std;

Farm::Farm(MainWindow *prt) : Building(prt)
{
    Building::setName("Farm");
    Building::setHeight(5);
    Building::setWidth(5);
    m_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(ENTITY_FARM));
    draw_surface.x = 0;
    draw_surface.y = 0;
    draw_surface.w = 5 * DEFAULT_WINDOWS_TILE;
    draw_surface.h = 5 * DEFAULT_WINDOWS_TILE;
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