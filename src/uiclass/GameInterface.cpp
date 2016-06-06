#include <Constants.hpp>
#include <model/Farm.hpp>
#include <uiclass/GameInterface.h>
#include <utilities/RessourceManager.h>

GameInterface::GameInterface(MainWindow *parent, SDLPoller *poller): Widget(parent)
{
	m_poller = poller;
	m_map = new Map(getParent());
	m_minimap = new Minimap(getParent(), getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH / 2, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT / 2, m_map);

	m_poller->subscribe(m_map);

	m_menu_rect.x = GAME_INTERFACE_BUILDING_MENU_WIDTH;
	m_menu_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	m_menu_rect.w = getParent()->getWidth() - GAME_INTERFACE_BUILDING_MENU_WIDTH;
	m_menu_rect.h = GAME_INTERFACE_MENU_HEIGHT;

	m_building_rect.x = 0;
	m_building_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	m_building_rect.w = GAME_INTERFACE_BUILDING_MENU_WIDTH;
	m_building_rect.h = GAME_INTERFACE_MENU_HEIGHT;

	m_map_rect.x = getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH;
	m_map_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
	m_map_rect.w = GAME_INTERFACE_MAP_WIDTH;
	m_map_rect.h = GAME_INTERFACE_MENU_HEIGHT;

	m_minimap->setPosition(getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH / 2 - m_minimap->getWidth() / 2, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT / 2 - m_minimap->getHeight() / 2);

	m_btn_home = new Button(getParent(), 0, m_building_rect.y, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
	m_btn_road = new Button(getParent(), 48, m_building_rect.y, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
	m_btn_school = new Button(getParent(), 96, m_building_rect.y, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
	m_btn_farm = new Button(getParent(), 0, m_building_rect.y + 48, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
	m_btn_cancel = new Button(getParent(), GAME_INTERFACE_BUILDING_MENU_WIDTH - 48, m_building_rect.y + 144, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game_Cancel), "");

	m_poller->subscribe(m_btn_home);
	m_poller->subscribe(m_btn_road);
	m_poller->subscribe(m_btn_school);
	m_poller->subscribe(m_btn_farm);
	m_poller->subscribe(m_btn_cancel);
	m_poller->subscribe(m_minimap);

	m_map->setDisplayHeight(getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT);
}

GameInterface::~GameInterface()
{
	delete m_map;
	delete m_btn_home;
	delete m_btn_road;
	delete m_btn_school;
	delete m_btn_farm;
	delete m_btn_cancel;
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
	SDL_RenderFillRect(getParent()->getRenderer(), &m_menu_rect);
	SDL_SetRenderDrawColor(getParent()->getRenderer(), 0, 255, 0, 255);
	SDL_RenderFillRect(getParent()->getRenderer(), &m_building_rect);
	SDL_SetRenderDrawColor(getParent()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(getParent()->getRenderer(), &m_map_rect);
	m_btn_home->draw();
	m_btn_road->draw();
	m_btn_school->draw();
	m_btn_farm->draw();
	m_btn_cancel->draw();
	m_minimap->draw();

	if (m_btn_farm->isClicked())
		m_map->setTmpBuilding(new Farm(getParent()));
	if (m_btn_cancel->isClicked())
		m_map->setTmpBuilding(NULL);
}
