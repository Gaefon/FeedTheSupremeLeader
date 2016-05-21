#include <SDL.h>

#include <model/Map.h>

#include <Constants.hpp>

Map::Map(MainWindow *par)
{
	m_width = DEFAULT_MAP_WIDTH;
    m_height = DEFAULT_MAP_HEIGHT;
    m_parent = par;
    m_is_moving = false;
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
	SDL_SetRenderDrawColor(m_parent->getRenderer(), 0, 255, 0, 255);
	for (unsigned int i = 0; i <= m_height; i++)
		SDL_RenderDrawLine(m_parent->getRenderer(), 0, i * DEFAULT_WINDOWS_TILE, m_width * DEFAULT_WINDOWS_TILE, i * DEFAULT_WINDOWS_TILE);

	for (unsigned int i = 0; i <= m_width; i++)
		SDL_RenderDrawLine(m_parent->getRenderer(), i * DEFAULT_WINDOWS_TILE, 0, i * DEFAULT_WINDOWS_TILE, m_height * DEFAULT_WINDOWS_TILE);
}

void Map::drawMap()
{
	drawMapGrid();
}


void Map::onSdlEventReceived(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_is_moving = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_is_moving = false;
			break;
		case SDL_MOUSEMOTION:
			if (m_is_moving == true)
			{
				//event.motion.x
				//event.motion.y
			}
			break;
	}
}
