#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SDL.h>
#include <uiclass/MainWindow.hpp>
#include <utilities/Observer/SdlObserver.h>

class Button: public SdlObserver
{
	private:
		MainWindow *m_parent;
		
		SDL_Rect dst;
		SDL_Rect src;
		SDL_Texture *m_button_tex;

	public:
		Button(MainWindow *prnt, int pos_x, int pos_y, std::string file_name);
		~Button();
		void onSdlEventReceived(SDL_Event event);
		void draw();
};

#endif