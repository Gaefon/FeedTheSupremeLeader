#include <iostream>
#include <Constants.hpp>
#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>
#include <utilities/RessourceManager.h>

using namespace std;
Building::Building()
{
    //ctor
}

Building::Building(MainWindow *prt)
{
    m_parent = prt;
}

void Building::setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int Building::getWidth()
{
	return m_width;
}

void Building::setHeight(unsigned int val)
{
	m_height = val;
}

unsigned int Building::getHeight()
{
	return m_height;
}

MainWindow *Building::getParent()
{
    return m_parent;
}

string Building::getName()
{
	return m_name;
}

void Building::setName(string val)
{
	m_name = val;
}
void Building::drawBuilding()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Rect src, dst;

    src.x = 0;
    src.y = 0;
    src.w = getWidth();
    src.h = getHeight();
    dst.x = x - getWidth() / 2;
    dst.y = y - getHeight() / 2;
    dst.w = getWidth();
    dst.h = getHeight();

    m_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(),  RessourceManager::getInstance()->getSurface(ENTITY_FARM));
    SDL_RenderCopy(getParent()->getRenderer(), m_texture, &src, &dst);
}

Building::~Building()
{
	//dtor
}
