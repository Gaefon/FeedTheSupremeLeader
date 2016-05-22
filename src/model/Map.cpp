#include <SDL.h>

#include <model/Map.h>
#include <Constants.hpp>



using namespace std;

Map::Map(MainWindow *par)
{
	m_width = DEFAULT_MAP_WIDTH;
	m_height = DEFAULT_MAP_HEIGHT;
	m_margin = DEFAULT_MAP_MARGIN;
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
	/*list<Building *>::iterator it;
	for (it = m_list_building.begin(); it != m_list_building.end(); it++)
		(*it)->drawBuilding();*/
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

				if (m_map_relative_position_x >= 0)
					m_map_relative_position_x = 0;
				if (m_map_relative_position_y >= 0)
					m_map_relative_position_y = 0;
				/*int calc_x_pos = m_map_relative_position_x + event.motion.x - m_previous_x;
				int calc_y_pos = m_map_relative_position_y + event.motion.y - m_previous_y;
				if(calc_x_pos <= (int)(m_width + m_margin) )
				{
					m_map_relative_position_x = calc_x_pos;
					m_previous_x = event.motion.x;
				}
				if(calc_y_pos <= (int)(m_height + m_margin))
				{
					m_map_relative_position_y = calc_y_pos;
					m_previous_y = event.motion.y;
				}*/
			}
			break;
	}
}
