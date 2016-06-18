#include <SDL.h>
#include <math.h>
#include <model/Building.hpp>
#include <model/Farm.hpp>
#include <model/House.h>
#include <model/Road.h>
#include <model/School.h>
#include <model/Map.h>
#include <Constants.hpp>
#include <utilities/BuildingHelper.h>
#include <helper/RectHelper.h>
#include <utilities/RessourceManager.h>
#include <utilities/Config.h>
#include <utilities/sounds/sounds.h>

using namespace std;

Map::Map(MainWindow *par)
{
	m_width = DEFAULT_MAP_WIDTH;
	m_height = DEFAULT_MAP_HEIGHT;
	m_margin = DEFAULT_MAP_MARGIN;
	m_parent = par;
	m_is_moving = false;
	m_is_button_down = false;
	m_map_relative_position_x = 0;
	m_map_relative_position_y = 0;

	m_tmp_building = NULL;

	m_display_width = m_parent->getWidth();
	m_display_height = m_parent->getHeight();

	m_move_sensivity = Config::getInstance()->getInt(Config::MapSensivity);
	m_is_map_move_enabled = true;

	m_texture_tile = SDL_CreateTextureFromSurface(m_parent->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::Default_tile));
	draw_tile_surface.x = 0;
	draw_tile_surface.y = 0;
	draw_tile_surface.w = DEFAULT_WINDOWS_TILE;
	draw_tile_surface.h = DEFAULT_WINDOWS_TILE;

	m_map_surface.x = 0;
	m_map_surface.y = 0;
	m_map_surface.w = m_parent->getWidth();
	m_map_surface.h = m_parent->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
}

Map::~Map()
{
	delete m_tmp_building;
	SDL_DestroyTexture(m_texture_tile);
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

int Map::getTilePosX()
{
	return roundf(m_map_relative_position_x / DEFAULT_WINDOWS_TILE);
}

int Map::getTilePosY()
{
	return roundf(m_map_relative_position_y / DEFAULT_WINDOWS_TILE);
}

void Map::setTileMapPos(int pos_x, int pos_y)
{
	m_map_relative_position_x = - pos_x * DEFAULT_WINDOWS_TILE;
	m_map_relative_position_y = - pos_y * DEFAULT_WINDOWS_TILE;
}

void Map::setEnabled(bool enable)
{
	m_is_map_move_enabled = enable;
}

void Map::setTmpBuilding(Building *tmp)
{
	if (m_tmp_building != NULL)
		delete m_tmp_building;
	m_tmp_building = tmp;
}

void Map::removeBuilding(Building *to_remove)
{
	m_list_building.remove(to_remove);
	Sounds::getInstance()->playWav(RessourceManager::getInstance()->getSound(RessourceManager::BuildingDestroy));
}

list<Building *> *Map::getBuildings()
{
	return &m_list_building;
}

void Map::drawMapGrid()
{
	for (unsigned int i = 0; i < m_height; ++i)
	{
		draw_tile_surface.y = i * DEFAULT_WINDOWS_TILE + m_map_relative_position_y;
		if (draw_tile_surface.y + draw_tile_surface.w < 0)
			continue;
		for (unsigned int j = 0; j < m_width; j++)
		{
			draw_tile_surface.x = j * DEFAULT_WINDOWS_TILE + m_map_relative_position_x;
			if (draw_tile_surface.x + draw_tile_surface.w < 0)
				continue;
			SDL_RenderCopy(m_parent->getRenderer(), m_texture_tile, NULL, &draw_tile_surface);
			if (draw_tile_surface.x >= m_map_surface.w)
				break;
		}
		if (draw_tile_surface.y >= m_map_surface.h)
			break;
	}

	/*for (unsigned int i = 0; i <= m_height; ++i)
	{
		SDL_SetRenderDrawColor(m_parent->getRenderer(), 0, 255, i * 2, 255);
		SDL_RenderDrawLine(m_parent->getRenderer(), m_map_relative_position_x, m_map_relative_position_y + i * DEFAULT_WINDOWS_TILE, m_map_relative_position_x + m_width * DEFAULT_WINDOWS_TILE, m_map_relative_position_y + i * DEFAULT_WINDOWS_TILE);
	}

	for (unsigned int i = 0; i <= m_width; i++)
	{
		SDL_SetRenderDrawColor(m_parent->getRenderer(), 255, i * 2, 0, 255);
		SDL_RenderDrawLine(m_parent->getRenderer(), m_map_relative_position_x + i * DEFAULT_WINDOWS_TILE, m_map_relative_position_y, m_map_relative_position_x + i * DEFAULT_WINDOWS_TILE, m_map_relative_position_y + m_height * DEFAULT_WINDOWS_TILE);
	}*/
}

void Map::checkCursorPosition()
{
	if(m_is_map_move_enabled && m_parent->getFlags() & SDL_WINDOW_INPUT_FOCUS)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_x += m_move_sensivity;
			if (y > (m_parent->getHeight() / 2) + m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y -= m_move_sensivity;
			else if (y < (m_parent->getHeight() / 2) - m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y += m_move_sensivity;
		}
		else if (y <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_y += m_move_sensivity;
			if (x > (m_parent->getWidth() / 2) + m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x -= m_move_sensivity;
			else if (x < (m_parent->getWidth() / 2) - m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x += m_move_sensivity;
		}
		else if (m_parent->getWidth() - x <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_x -= m_move_sensivity;
			if (y > (m_parent->getHeight() / 2) + m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y -= m_move_sensivity;
			else if (y < (m_parent->getHeight() / 2) - m_parent->getHeight() * WIDTH_DEAD_RATIO)
				m_map_relative_position_y += m_move_sensivity;
		}
		else if (m_parent->getHeight() - y <= MAP_BORDER_WIDTH_MOVE)
		{
			m_map_relative_position_y -= m_move_sensivity;
			if (x > (m_parent->getWidth() / 2) + m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x -= m_move_sensivity;
			else if (x < (m_parent->getWidth() / 2) - m_parent->getWidth() * HEIGHT_DEAD_RATIO)
				m_map_relative_position_x += m_move_sensivity;
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

MapPoller *Map::getPoller()
{
	return &m_poller;
}

void Map::drawMap()
{
	checkCursorPosition();
	drawMapGrid();
	list<Building *>::iterator it;
	for (it = m_list_building.begin(); it != m_list_building.end(); it++)
	{
		(*it)->drawBuilding(m_map_relative_position_x, m_map_relative_position_y);
	}

	if (m_tmp_building != NULL)
	{
		m_tmp_building->drawBuilding(m_map_relative_position_x, m_map_relative_position_y);
		if (!BuildingHelper::isBuildingPlaceValid(m_list_building ,m_tmp_building))
		{
			SDL_Rect rect_overlay_building;

			rect_overlay_building.x = m_tmp_building->getPosX() * DEFAULT_WINDOWS_TILE + m_map_relative_position_x;
			rect_overlay_building.y = m_tmp_building->getPosY() * DEFAULT_WINDOWS_TILE + m_map_relative_position_y;
			rect_overlay_building.w = m_tmp_building->getDisplayWidth();
			rect_overlay_building.h = m_tmp_building->getDisplayHeight();
			SDL_SetRenderDrawColor(m_parent->getRenderer(), 255, 0, 0, 64);
			SDL_RenderFillRect(m_parent->getRenderer(), &rect_overlay_building);
		}
	}
}

void Map::addBuildingIfPossible()
{
	if (BuildingHelper::isBuildingPlaceValid(m_list_building ,m_tmp_building))
	{
		Building *tmp_copy = BuildingHelper::getCopyOfTmpBuilding(m_tmp_building, m_parent);
		Sounds::getInstance()->playWav(RessourceManager::getInstance()->getSound(RessourceManager::BuildingBuild));
		m_list_building.push_front(m_tmp_building);
		tmp_copy->setPosX(m_tmp_building->getPosX());
		tmp_copy->setPosY(m_tmp_building->getPosY());
		m_tmp_building = tmp_copy;
	}
}

bool Map::onSdlEventReceived(SDL_Event event)
{
	bool rtn_val = false;
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (RectHelper::isInRect(&m_map_surface, event.button.x, event.button.y))
				{
					m_is_button_down = true;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			m_is_button_down = false;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (RectHelper::isInRect(&m_map_surface, event.button.x, event.button.y))
				{
				    if (m_tmp_building != NULL)
					{
						addBuildingIfPossible();
						rtn_val = true;
					}
					else
					{
						unsigned int x_clicked = (event.button.x - m_map_relative_position_x) / DEFAULT_WINDOWS_TILE;
						unsigned int y_clicked = (event.button.y - m_map_relative_position_y) / DEFAULT_WINDOWS_TILE;
						bool did_notify = false;
						for (list<Building *>::iterator it = m_list_building.begin(); it != m_list_building.end(); ++it)
						{
							if (x_clicked >= (*it)->getPosX() && x_clicked < ((*it)->getPosX() + (*it)->getWidth()) &&
								y_clicked >= (*it)->getPosY() && y_clicked < ((*it)->getPosY() + (*it)->getHeight()))
							{
								m_poller.notifyBuildingSelected(*it);
								did_notify = true;
								break;
							}
						}
						if (!did_notify)
							m_poller.notifyBuildingSelected(NULL);
					}
				}
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (RectHelper::isInRect(&m_map_surface, event.button.x, event.button.y) && m_tmp_building != NULL)
				{
					setTmpBuilding(NULL);
					rtn_val = true;
				}
			}
			break;
		case SDL_MOUSEMOTION:
			if (!RectHelper::isInRect(&m_map_surface, event.motion.x, event.motion.y))
				m_is_button_down = false;
			if (m_tmp_building != NULL)
			{
				int pos_grid_x = roundf((event.motion.x - m_map_relative_position_x - (m_tmp_building->getDisplayWidth() / 2.0f)) / (float) DEFAULT_WINDOWS_TILE);
				int pos_grid_y = roundf((event.motion.y - m_map_relative_position_y - (m_tmp_building->getDisplayHeight() / 2.0f)) / (float) DEFAULT_WINDOWS_TILE);

				if (pos_grid_x < 0)
					pos_grid_x = 0;
				else if (pos_grid_x >= DEFAULT_MAP_WIDTH - (int) m_tmp_building->getWidth())
					pos_grid_x = DEFAULT_MAP_WIDTH - m_tmp_building->getWidth();

				if (pos_grid_y < 0)
					pos_grid_y = 0;
				else if (pos_grid_y >= DEFAULT_MAP_HEIGHT - (int) m_tmp_building->getHeight())
					pos_grid_y = DEFAULT_MAP_HEIGHT - m_tmp_building->getHeight();

				m_tmp_building->setPosX(pos_grid_x);
				m_tmp_building->setPosY(pos_grid_y);

				if (m_is_button_down == true && m_tmp_building->isDraggable())
					addBuildingIfPossible();
			}
			break;
	}
	return rtn_val;
}
