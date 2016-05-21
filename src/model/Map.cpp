#include <SDL.h>

#include <model/Map.h>

#include <Constants.hpp>

#include <iostream>

using namespace std;

Map::Map(MainWindow *par)
{
	m_width = DEFAULT_MAP_WIDTH;
	m_height = DEFAULT_MAP_HEIGHT;
	m_parent = par;
	m_is_moving = false;
	m_map_relative_position_x = 0;
	m_map_relative_position_y = 0;
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

void Map::drawMapGrid()
{
	
	for (unsigned int i = 0; i <= m_height; ++i)
	{
		SDL_SetRenderDrawColor(m_parent->getRenderer(), 0, 255, i * 2, 255);
		SDL_RenderDrawLine(m_parent->getRenderer(), m_map_relative_position_x, m_map_relative_position_y + i * DEFAULT_WINDOWS_TILE, m_map_relative_position_x + m_width * DEFAULT_WINDOWS_TILE, m_map_relative_position_y + i * DEFAULT_WINDOWS_TILE);
	}

	for (unsigned int i = 0; i <= m_width; i++)
	{
		SDL_SetRenderDrawColor(m_parent->getRenderer(), 255, i * 2, 0, 255);
		SDL_RenderDrawLine(m_parent->getRenderer(), m_map_relative_position_x + i * DEFAULT_WINDOWS_TILE, m_map_relative_position_y, m_map_relative_position_x + i * DEFAULT_WINDOWS_TILE, m_map_relative_position_y + m_height * DEFAULT_WINDOWS_TILE);
	}
}

void Map::drawMap()
{
	drawMapGrid();
	SDL_SetRenderDrawColor(m_parent->getRenderer(), 0, 0, 0, 255);
}


void Map::onSdlEventReceived(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_is_moving = true;
				m_previous_x = event.button.x;
				m_previous_y = event.button.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_is_moving = false;
			break;
		case SDL_MOUSEMOTION:
			if (m_is_moving == true)
			{
				m_map_relative_position_x += event.motion.x - m_previous_x;
				m_map_relative_position_y += event.motion.y - m_previous_y;
				m_previous_x = event.motion.x;
				m_previous_y = event.motion.y;
				cout << "X : " << m_map_relative_position_x << " // Y : " << m_map_relative_position_y << endl;
				//event.motion.x
				//event.motion.y
			}
			break;
	}
}
