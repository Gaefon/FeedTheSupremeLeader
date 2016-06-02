#include <iostream>
#include <Constants.hpp>
#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>
#include <utilities/RessourceManager.h>

using namespace std;

Building::Building(MainWindow *prt)
{
	m_parent = prt;
}

unsigned int Building::getWidth()
{
	return m_width;
}

unsigned int Building::getDisplayWidth()
{
	return m_width * DEFAULT_WINDOWS_TILE;
}

void Building::setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int Building::getHeight()
{
	return m_height;
}

unsigned int Building::getDisplayHeight()
{
	return m_height * DEFAULT_WINDOWS_TILE;
}

void Building::setHeight(unsigned int val)
{
	m_height = val;
}

unsigned int Building::getPosX()
{
	return m_pos_x;
}

void Building::setPosX(unsigned int val)
{
	m_pos_x = val;
}

unsigned int Building::getPosY()
{
	return m_pos_y;
}

void Building::setPosY(unsigned int val)
{
	m_pos_y = val;
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


Building::~Building()
{
	//dtor
}
