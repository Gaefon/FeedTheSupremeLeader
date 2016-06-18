#include <iostream>
#include <string>
#include <sstream>
#include <uiclass/GameInterface.h>
#include <Constants.hpp>
#include <GameStrings.h>
#include <model/Farm.hpp>
#include <model/School.h>
#include <model/House.h>
#include <model/Road.h>
#include <model/Village.h>
#include <utilities/RessourceManager.h>

using namespace std;

GameInterface::GameInterface(MainWindow *parent, SDLPoller *poller, Village *village): Widget(parent)
{
	m_poller = poller;
	m_village = village;
	m_building_clicked = NULL;
	m_map = new Map(getParent());
	m_minimap = new Minimap(getParent(), getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH / 2, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT / 2, m_map);

	m_food_to_send = 1;

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

	m_counter_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::Counter_bg));
	m_counter1_rect.x = getParent()->getWidth() - 127;
	m_counter1_rect.y = 20;
	m_counter1_rect.w = 97;
	m_counter1_rect.h = 29;

	m_counter2_rect.x = getParent()->getWidth() - 227;
	m_counter2_rect.y = 20;
	m_counter2_rect.w = 97;
	m_counter2_rect.h = 29;

	m_minimap->setPosition(getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH / 2 - m_minimap->getWidth() / 2, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT / 2 - m_minimap->getHeight() / 2);

	m_btn_home = new Button(getParent(), 12, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_House_Game), "");
	m_btn_road = new Button(getParent(), 60, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Road_Game), "");
	m_btn_school = new Button(getParent(), 108, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_School_Game), "");
	m_btn_farm = new Button(getParent(), 156, m_building_rect.y + 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Farm_Game), "");
	m_btn_cancel = new Button(getParent(), GAME_INTERFACE_BUILDING_MENU_WIDTH - 48 - 12, m_building_rect.y + 144 - 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game_Cancel), "");
	m_btn_destroy_build = new Button(getParent(), GAME_INTERFACE_BUILDING_MENU_WIDTH + 12, getParent()->getHeight() - 48 - 12, RessourceManager::getInstance()->getSurface(RessourceManager::Button_Menu_Game_Cancel), "");
	m_btn_destroy_build->hide();

	m_btn_add_food = new Button(getParent(), getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH - 48, getParent()->getHeight() - 96, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Small_Button), "+");
	m_btn_remove_food = new Button(getParent(), getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH - 158, getParent()->getHeight() - 96, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Small_Button), "-");
	m_btn_send_food = new Button(getParent(), getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH - 158, getParent()->getHeight() - 48, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Default_Button), "Send food");

	m_label_buiding_name = new Label(getParent(), GAME_INTERFACE_BUILDING_MENU_WIDTH + 24, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT + 24, "");
	m_label_buiding_name->setFont(RessourceManager::LatoFont20);
	m_label_buiding_population = new Label(getParent(), GAME_INTERFACE_BUILDING_MENU_WIDTH + 24, getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT + 48, "");
	m_label_buiding_population->setFont(RessourceManager::LatoFont20);
	m_label_population= new Label(getParent(), getParent()->getWidth() - 205, 22, "");
	m_label_population->setFont(RessourceManager::LatoFont20);
	m_label_food = new Label(getParent(), getParent()->getWidth() - 105, 22, "");
	m_label_food->setFont(RessourceManager::LatoFont20);

	m_label_food_to_send = new Label(getParent(), getParent()->getWidth() - GAME_INTERFACE_MAP_WIDTH - 100, getParent()->getHeight() - 96, "0");
	m_label_food_to_send->setFont(RessourceManager::LatoFont20);

	m_commissar = new Commissar(getParent(), 0, 0);

	m_minimap->setToCenter();

	subscribeInterface();

	m_map->getPoller()->subscribe(this);
	m_map->setDisplayHeight(getParent()->getHeight() - GAME_INTERFACE_MENU_HEIGHT);
	village->setMap(m_map);
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
	delete m_btn_destroy_build;

	delete m_label_buiding_name;
	delete m_label_buiding_population;
	delete m_label_population;
	delete m_label_food;

	delete m_btn_add_food;
	delete m_btn_remove_food;
	delete m_btn_send_food;
}

int GameInterface::getWidth()
{
	return getParent()->getWidth();
}

int GameInterface::getHeight()
{
	return getParent()->getHeight();
}

void GameInterface::drawRessourceCounter()
{
	std::stringstream ss;
	ss << m_village->getPopulation();
	string str = ss.str();
	ss.str("");
	m_label_population->setText(str);
	m_label_population->draw();
	ss << m_village->getFood();
	str = ss.str();
	m_label_food->setText(str);
	m_label_food->draw();
}

void GameInterface::draw()
{
	m_map->drawMap();
	SDL_SetRenderDrawColor(getParent()->getRenderer(), 0, 0, 255, 255);
	SDL_RenderFillRect(getParent()->getRenderer(), &m_menu_rect);

	SDL_RenderCopy(getParent()->getRenderer(), m_button_back_texture, NULL, &m_building_rect);
	SDL_RenderCopy(getParent()->getRenderer(), m_map_back_texture, NULL, &m_map_rect);
	m_btn_home->draw();
	m_btn_road->draw();
	m_btn_school->draw();
	m_btn_farm->draw();
	m_btn_cancel->draw();
	m_btn_destroy_build->draw();

	m_btn_add_food->draw();
	m_btn_remove_food->draw();
	m_btn_send_food->draw();

	m_minimap->draw();
	m_label_buiding_name->draw();
	m_label_buiding_population->draw();

	SDL_RenderCopy(getParent()->getRenderer(), m_counter_texture, NULL, &m_counter1_rect);
	SDL_RenderCopy(getParent()->getRenderer(), m_counter_texture, NULL, &m_counter2_rect);
	drawRessourceCounter();

	m_commissar->draw();

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

	if (m_btn_add_food->isPressed())
	{
		m_food_to_send++;
		if (m_food_to_send > m_village->getFood())
			m_food_to_send = m_village->getFood();
		m_label_food_to_send->setText(std::to_string(m_food_to_send));

	}
	if (m_btn_remove_food->isPressed())
	{
		m_food_to_send--;
		if (m_food_to_send < 1)
			m_food_to_send = 1;
		m_label_food_to_send->setText(std::to_string(m_food_to_send));
	}

	if (m_btn_send_food->isClicked() && m_food_to_send <= m_village->getFood())
	{
		m_commissar->displayText(COMMISSAR_SEND_FOOD, 2000);
		m_village->sendFood(m_food_to_send);
	}

	m_label_food_to_send->draw();

	if (m_btn_destroy_build->isClicked() && m_building_clicked != NULL)
	{
		m_village->destroyBuilding(m_building_clicked);
		m_map->removeBuilding(m_building_clicked);
		onBuidingClicked(NULL);
	}
}

void GameInterface::subscribeInterface()
{
	m_map->setEnabled(true);
	m_poller->subscribe(m_map);
	m_poller->subscribe(m_btn_home);
	m_poller->subscribe(m_btn_road);
	m_poller->subscribe(m_btn_school);
	m_poller->subscribe(m_btn_farm);
	m_poller->subscribe(m_btn_cancel);
	m_poller->subscribe(m_btn_destroy_build);
	m_poller->subscribe(m_btn_add_food);
	m_poller->subscribe(m_btn_remove_food);
	m_poller->subscribe(m_btn_send_food);
	m_poller->subscribe(m_minimap);
}
void GameInterface::unsubscribeInterface()
{
	m_map->setEnabled(false);
	m_poller->unSubscribe(m_map);
	m_poller->unSubscribe(m_btn_home);
	m_poller->unSubscribe(m_btn_road);
	m_poller->unSubscribe(m_btn_school);
	m_poller->unSubscribe(m_btn_farm);
	m_poller->unSubscribe(m_btn_cancel);
	m_poller->unSubscribe(m_btn_destroy_build);
	m_poller->unSubscribe(m_btn_add_food);
	m_poller->unSubscribe(m_btn_remove_food);
	m_poller->unSubscribe(m_btn_send_food);
	m_poller->unSubscribe(m_minimap);
}

bool GameInterface::onBuidingClicked(Building *building)
{
	m_building_clicked = building;
	if (m_building_clicked != NULL)
	{
		m_label_buiding_name->setText(m_building_clicked->getName());
		if (m_building_clicked->getMaxOccupancy() > 0)
		{
			stringstream tmp;
			tmp << m_building_clicked->getOccupancy() << " / " << m_building_clicked->getMaxOccupancy();
			m_label_buiding_population->setText(tmp.str());
		}
		else if (m_building_clicked->getMaxWorkers() > 0)
		{
			stringstream tmp;
			tmp << m_building_clicked->getWorkers() << " / " << m_building_clicked->getMaxWorkers();
			m_label_buiding_population->setText(tmp.str());
		}
		else
			m_label_buiding_population->setText("");
		m_btn_destroy_build->show();
	}
	else
	{
		m_label_buiding_name->setText("");
		m_label_buiding_population->setText("");
		m_btn_destroy_build->hide();
	}
	return true;
}

bool GameInterface::onBuildingBuildt(Building *building)
{
	if (building->getPrice() > m_village->getMerit())
	{
		m_commissar->displayText(COMMISSAR_NOT_ENOUGH_MERIT);
		return false;
	}
	m_village->addBuilding(building);
	return true;
}
