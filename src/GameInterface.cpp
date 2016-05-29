#include <Constants.hpp>
#include <GameInterface.h>
#include <iostream>

using namespace std;

GameInterface::GameInterface(MainWindow *parent, SDLPoller *poller)
{
	m_parent = parent;
	m_poller = poller;
	m_map = new Map(m_parent);
	m_poller->subscribe(m_map);
	menu_rect.x = 0;
	menu_rect.y = m_parent->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	menu_rect.w = m_parent->getWidth();
	menu_rect.h = GAME_INTERFACE_MENU_HEIGHT;
	m_map->setDisplayHeight(m_parent->getHeight() - GAME_INTERFACE_MENU_HEIGHT);
}

GameInterface::~GameInterface()
{
	delete m_map;
}

void GameInterface::draw()
{
	m_map->drawMap();
	SDL_SetRenderDrawColor(m_parent->getRenderer(), 0, 0, 255, 255);
	SDL_RenderFillRect(m_parent->getRenderer(), &menu_rect);
}