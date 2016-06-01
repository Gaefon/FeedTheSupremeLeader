#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <SDL.h>

#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>
#include <uiclass/Button.h>
#include <utilities/Poller/SDLPoller.h>
#include <model/Map.h>

class GameInterface: public Widget
{
	private:
		SDLPoller *m_poller;
		Map *m_map;
		SDL_Rect menu_rect;
		SDL_Rect map_rect;
		SDL_Rect building_rect;

		Button *btn_home;
		Button *btn_road;
		Button *btn_school;

	public:
		GameInterface(MainWindow *parent, SDLPoller *poller);
		~GameInterface();
		int getWidth();
		int getHeight();
		void draw();
};

#endif