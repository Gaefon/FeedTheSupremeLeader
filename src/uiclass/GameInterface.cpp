#include <iostream>
#include <Constants.hpp>
#include <model/Farm.hpp>
#include <model/School.h>
#include <model/House.h>
#include <model/Road.h>
#include <uiclass/GameInterface.h>
#include <utilities/RessourceManager.h>

using namespace std;

GameInterface::GameInterface(MainWindow *parent, SDLPoller *poller, VillagePoller *village_poller): Widget(parent)
{
    m_poller = poller;
    m_village_poller = village_poller;
    m_map = new Map(getParent());
    m_minimap = new Minimap(getParent(), getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH / 2, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT / 2, m_map);

    m_poller->subscribe(m_map);

    m_menu_rect.x = GAME_INTERFACE_BUILDING_MENU_WIDTH;
    m_menu_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
    m_menu_rect.w = getParent()->getWidth() - GAME_INTERFACE_BUILDING_MENU_WIDTH - GAME_INTERFACE_MAP_WIDTH;
    m_menu_rect.h = GAME_INTERFACE_MENU_HEIGHT;

	m_button_back_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::BackgroundMenuButton));
    m_building_rect.x = 0;
    m_building_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
    m_building_rect.w = GAME_INTERFACE_BUILDING_MENU_WIDTH;
    m_building_rect.h = GAME_INTERFACE_MENU_HEIGHT;

    m_map_back_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::BackgroundMenuMap));
    m_map_rect.x = getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH;
    m_map_rect.y = getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT;
    m_map_rect.w = GAME_INTERFACE_MAP_WIDTH;
    m_map_rect.h = GAME_INTERFACE_MENU_HEIGHT;

    m_minimap->setPosition(getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH / 2 - m_minimap->getWidth() / 2, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT / 2 - m_minimap->getHeight() / 2);

    m_btn_home = new Button(getParent(), 12, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
    m_btn_road = new Button(getParent(), 60, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
    m_btn_school = new Button(getParent(), 108, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
    m_btn_farm = new Button(getParent(), 156, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game), "");
    m_btn_cancel = new Button(getParent(), GAME_INTERFACE_BUILDING_MENU_WIDTH - 48 - 12, m_building_rect.y + 144 - 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game_Cancel), "");

    m_label_buiding_name = new Label(getParent(), GAME_INTERFACE_BUILDING_MENU_WIDTH + 24, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT + 24, "");
    m_label_buiding_name->setFont(RessourceManager::LatoFont20);

    m_poller->subscribe(m_btn_home);
    m_poller->subscribe(m_btn_road);
    m_poller->subscribe(m_btn_school);
    m_poller->subscribe(m_btn_farm);
    m_poller->subscribe(m_btn_cancel);
    m_poller->subscribe(m_minimap);

    m_map->getPoller()->subscribe(this);

    m_map->setDisplayHeight(getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT);
}

GameInterface::~GameInterface()
{
	SDL_DestroyTexture(m_map_back_texture);

    delete m_map;
    delete m_btn_home;
    delete m_btn_road;
    delete m_btn_school;
    delete m_btn_farm;
    delete m_btn_cancel;

    delete m_label_buiding_name;
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
	/*SDL_SetRenderDrawColor(getParent()->getRenderer(), 48, 48, 48, 255);
	SDL_RenderFillRect(getParent()->getRenderer(), &m_building_rect);*/

	SDL_RenderCopy(getParent()->getRenderer(), m_button_back_texture, NULL, &m_building_rect);
	SDL_RenderCopy(getParent()->getRenderer(), m_map_back_texture, NULL, &m_map_rect);
	m_btn_home->draw();
	m_btn_road->draw();
	m_btn_school->draw();
	m_btn_farm->draw();
	m_btn_cancel->draw();
	m_minimap->draw();
	m_label_buiding_name->draw();

	if (m_btn_home->isClicked())
		m_map->setTmpBuilding(new House(getParent()));
	if (m_btn_school->isClicked())
		m_map->setTmpBuilding(new School(getParent()));
	if (m_btn_farm->isClicked())
		m_map->setTmpBuilding(new Farm(getParent()));
	if (m_btn_road->isClicked())
		m_map->setTmpBuilding(new Road(getParent()));
	if (m_btn_cancel->isClicked())
		m_map->setTmpBuilding(NULL);
}

bool GameInterface::onBuidingClicked(Building *building)
{
    if (building != NULL)
    {
        m_label_buiding_name->setText(building->getName());
    }
    else
    {
        m_label_buiding_name->setText("");
    }
    return true;
}

bool GameInterface::onBuildingBuilt(Building *building)
{
    if (building != NULL)
    {
        m_village_poller->subscribe(building);
    }
    return true;
}

