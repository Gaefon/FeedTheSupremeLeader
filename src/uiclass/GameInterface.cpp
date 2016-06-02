#include <Constants.hpp>
#include <model/Farm.hpp>
#include <uiclass/GameInterface.h>
#include <utilities/RessourceManager.h>

GameInterface::GameInterface(MainWindow *parent, SDLPoller *poller): Widget(parent)
{
	m_poller = poller;
	m_map = new Map(getParent());
	m_poller->subscribe(m_map);

	menu_rect.x = GAME_INTERFACE_BUILDING_MENU_WIDTH;
	menu_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	menu_rect.w = getParent()->getWidth() - GAME_INTERFACE_BUILDING_MENU_WIDTH;
	menu_rect.h = GAME_INTERFACE_MENU_HEIGHT;

	building_rect.x = 0;
	building_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	building_rect.w = GAME_INTERFACE_BUILDING_MENU_WIDTH;
	building_rect.h = GAME_INTERFACE_MENU_HEIGHT;

	map_rect.x = getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH;
	map_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	map_rect.w = GAME_INTERFACE_MAP_WIDTH;
	map_rect.h = GAME_INTERFACE_MENU_HEIGHT;

	btn_home = new Button(getParent(), 0, building_rect.y, RessourceManager::getInstance()->getSurface(BTN_MENU_GAME), "");
	btn_road = new Button(getParent(), 48, building_rect.y, RessourceManager::getInstance()->getSurface(BTN_MENU_GAME), "");
	btn_school = new Button(getParent(), 96, building_rect.y, RessourceManager::getInstance()->getSurface(BTN_MENU_GAME), "");
	btn_farm = new Button(getParent(), 0, building_rect.y + 48, RessourceManager::getInstance()->getSurface(BTN_MENU_GAME), "");

	m_poller->subscribe(btn_home);
	m_poller->subscribe(btn_road);
	m_poller->subscribe(btn_school);
	m_poller->subscribe(btn_farm);

	m_map->setDisplayHeight(getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT);
}

GameInterface::~GameInterface()
{
	delete m_map;
	delete btn_home;
	delete btn_road;
	delete btn_school;
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
	SDL_SetRenderDrawColor(getParent()->getRenderer(), 0, 255, 0, 255);
	SDL_RenderFillRect(getParent()->getRenderer(), &building_rect);
	SDL_SetRenderDrawColor(getParent()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(getParent()->getRenderer(), &map_rect);
	btn_home->draw();
	btn_road->draw();
	btn_school->draw();
	btn_farm->draw();

	if (btn_farm->isClicked())
		m_map->setTmpBuilding(new Farm(getParent()));
}