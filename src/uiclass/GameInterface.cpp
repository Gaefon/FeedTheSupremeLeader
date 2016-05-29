#include <Constants.hpp>
#include <uiclass/GameInterface.h>

GameInterface::GameInterface(MainWindow *parent, SDLPoller *poller): Widget(parent)
{
	m_poller = poller;
	m_map = new Map(getParent());
	m_poller->subscribe(m_map);
	menu_rect.x = 0;
	menu_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	menu_rect.w = getParent()->getWidth();
	menu_rect.h = GAME_INTERFACE_MENU_HEIGHT;
	m_map->setDisplayHeight(getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT);
}

GameInterface::~GameInterface()
{
	delete m_map;
}

int GameInterface::getWidth()
{
	return getParent()->getWidth();
}

int GameInterface::getHeight()
{
	return getParent()->getHeight();
}

void GameInterface::draw()
{
	m_map->drawMap();
	SDL_SetRenderDrawColor(getParent()->getRenderer(), 0, 0, 255, 255);
	SDL_RenderFillRect(getParent()->getRenderer(), &menu_rect);
}