#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <SDL.h>

#include <uiclass/MainWindow.hpp>
#include <utilities/Poller/SDLPoller.h>
#include <model/Map.h>

class GameInterface
{
	private:
		MainWindow *m_parent;
		SDLPoller *m_poller;
		Map *m_map;
		SDL_Rect menu_rect;

	public:
		GameInterface(MainWindow *parent, SDLPoller *poller);
		~GameInterface();
		void draw();
};

#endif