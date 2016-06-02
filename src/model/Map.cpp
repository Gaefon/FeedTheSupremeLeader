#include <SDL.h>
#include <model/Building.hpp>
#include <model/Farm.hpp>
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

	m_tmp_building = NULL;

	m_display_width = m_parent->getWidth();
	m_display_height = m_parent->getHeight();
}

Map::~Map()
{
	delete m_tmp_building;
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

void Map::setDisplayWidth(int new_w)
{
	m_display_width = new_w;
}

void Map::setDisplayHeight(int new_h)
{
	m_display_height = new_h;
}

void Map::setTmpBuilding(Building *tmp)
{
	if (m_tmp_building != NULL)
		delete m_tmp_building;
	m_tmp_building = tmp;
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

void Map::checkCursorPosition()
{
	if(m_parent->getFlags() & SDL_WINDOW_INPUT_FOCUS)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_x += MAP_MOVE_SENSIVITY;
			if (y > (m_parent->getHeight() / 2) + m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y -= MAP_MOVE_SENSIVITY;
			else if (y < (m_parent->getHeight() / 2) - m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y += MAP_MOVE_SENSIVITY;
		}
		else if (y <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_y += MAP_MOVE_SENSIVITY;
			if (x > (m_parent->getWidth() / 2) + m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x -= MAP_MOVE_SENSIVITY;
			else if (x < (m_parent->getWidth() / 2) - m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x += MAP_MOVE_SENSIVITY;
		}
		else if (m_parent->getWidth() - x <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_x -= MAP_MOVE_SENSIVITY;
			if (y > (m_parent->getHeight() / 2) + m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y -= MAP_MOVE_SENSIVITY;
			else if (y < (m_parent->getHeight() / 2) - m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y += MAP_MOVE_SENSIVITY;
		}
		else if (m_parent->getHeight() - y <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_y -= MAP_MOVE_SENSIVITY;
			if (x > (m_parent->getWidth() / 2) + m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x -= MAP_MOVE_SENSIVITY;
			else if (x < (m_parent->getWidth() / 2) - m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x += MAP_MOVE_SENSIVITY;
		}

		if (m_map_relative_position_x >= 0 + (int)(m_margin * DEFAULT_WINDOWS_TILE))
			m_map_relative_position_x = 0 + (int)(m_margin * DEFAULT_WINDOWS_TILE);
		if (m_map_relative_position_y >= 0 + (int)(m_margin * DEFAULT_WINDOWS_TILE))
			m_map_relative_position_y = 0 + (int)(m_margin * DEFAULT_WINDOWS_TILE);
		if (m_map_relative_position_x + m_width * DEFAULT_WINDOWS_TILE < m_display_width - (int)(m_margin * DEFAULT_WINDOWS_TILE))
			m_map_relative_position_x =  m_display_width - m_width * DEFAULT_WINDOWS_TILE - (int)(m_margin * DEFAULT_WINDOWS_TILE);
		if (m_map_relative_position_y + m_height * DEFAULT_WINDOWS_TILE < m_display_height - (int)(m_margin * DEFAULT_WINDOWS_TILE))
			m_map_relative_position_y = m_display_height - m_height * DEFAULT_WINDOWS_TILE - (int)(m_margin * DEFAULT_WINDOWS_TILE);
	}
}

void Map::drawMap()
{
	checkCursorPosition();
	list<Building *>::iterator it;
	for (it = m_list_building.begin(); it != m_list_building.end(); it++)
	{
		(*it)->drawBuilding(m_map_relative_position_x, m_map_relative_position_y);
	}

	if (m_tmp_building != NULL)
	{
		m_tmp_building->drawBuilding(m_map_relative_position_x, m_map_relative_position_y);
	}
	drawMapGrid();
	SDL_SetRenderDrawColor(m_parent->getRenderer(), 0, 0, 0, 255);
}


bool Map::onSdlEventReceived(SDL_Event event)
{
	switch (event.type)
	{
		/*case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_is_moving = true;
				m_previous_x = event.button.x;
				m_previous_y = event.button.y;
			}
			break;*/
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// si click sur la map
				if (m_tmp_building != NULL)
				{
					m_list_building.push_front(m_tmp_building);
					m_tmp_building = NULL;
				}
			}
			break;
		case SDL_MOUSEMOTION:
			if (m_tmp_building != NULL)
			{
				int pos_grid_x = (event.motion.x - m_map_relative_position_x) / DEFAULT_WINDOWS_TILE;
				int pos_grid_y = (event.motion.y - m_map_relative_position_y) / DEFAULT_WINDOWS_TILE;

				if (pos_grid_x < 0)
					pos_grid_x = 0;
				else if (pos_grid_x >= DEFAULT_MAP_WIDTH)
					pos_grid_x = DEFAULT_MAP_WIDTH - 1;

				if (pos_grid_y < 0)
					pos_grid_y = 0;
				else if (pos_grid_y >= DEFAULT_MAP_HEIGHT)
					pos_grid_y = DEFAULT_MAP_HEIGHT - 1;

				m_tmp_building->setPosX(pos_grid_x);
				m_tmp_building->setPosY(pos_grid_y);
			}
			break;
	}
	return false;
}
