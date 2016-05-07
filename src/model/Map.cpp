#include <model/Map.h>

#include <Constants.hpp>

Map::Map()
{
	m_width = DEFAULT_MAP_WIDTH;
    m_height = DEFAULT_MAP_HEIGHT;
}

Map::~Map()
{
}

void Map::setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int Map::getWidth()
{
	return m_width;
}

void Map::setHeight(unsigned int val)
{
	m_height = val;
}

unsigned int Map::getHeight()
{
	return m_height;
}
