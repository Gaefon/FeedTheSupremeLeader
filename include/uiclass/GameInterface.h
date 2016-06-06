#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <SDL.h>

#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>
#include <uiclass/Button.h>
#include <utilities/Poller/SDLPoller.h>
#include <utilities/Observer/MapObserver.h>
#include <model/Map.h>
#include <uiclass/Minimap.h>

class GameInterface: public Widget, public MapObserver
{
	private:
		SDLPoller *m_poller;
		Map *m_map;
		Minimap *m_minimap;
		SDL_Rect m_menu_rect;
		SDL_Rect m_map_rect;
		SDL_Rect m_building_rect;

		Button *m_btn_home;
		Button *m_btn_road;
		Button *m_btn_school;
		Button *m_btn_farm;
		Button *m_btn_cancel;

	public:
		GameInterface(MainWindow *parent, SDLPoller *poller);
		~GameInterface();
		int getWidth();
		int getHeight();
		void draw();
		bool onBuidingClicked(Building *building);
};

#endif