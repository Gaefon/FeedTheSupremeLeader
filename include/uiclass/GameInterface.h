#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <SDL.h>

#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>
#include <uiclass/Button.h>
#include <uiclass/Label.h>
#include <utilities/Poller/SDLPoller.h>
#include <utilities/Poller/VillagePoller.h>
#include <model/Village.h>
#include <utilities/Observer/MapObserver.h>
#include <model/Map.h>
#include <uiclass/Minimap.h>

class GameInterface: public Widget, public MapObserver
{
	private:
		SDLPoller *m_poller;
		VillagePoller *m_village_poller;
		Village *m_village;
		Map *m_map;
		Minimap *m_minimap;

		Building *m_building_clicked;

		SDL_Rect m_menu_rect;
		SDL_Rect m_map_rect;
		SDL_Rect m_building_rect;
		SDL_Rect m_counter1_rect;
        SDL_Rect m_counter2_rect;


		SDL_Texture *m_button_back_texture;
		SDL_Texture *m_map_back_texture;
		SDL_Texture *m_counter_texture;

		Button *m_btn_home;
		Button *m_btn_road;
		Button *m_btn_school;
		Button *m_btn_farm;
		Button *m_btn_cancel;
		Button *m_btn_destroy_build;

		Label *m_label_buiding_name;
		Label *m_label_population;
		Label *m_label_food;
		void drawRessourceCounter();

	public:
		GameInterface(MainWindow *parent, SDLPoller *poller, VillagePoller *village_poller, Village *village);
		~GameInterface();
		int getWidth();
		int getHeight();
		void draw();
		bool onBuidingClicked(Building *building);
		bool onBuildingBuilt(Building *building);
};

#endif
