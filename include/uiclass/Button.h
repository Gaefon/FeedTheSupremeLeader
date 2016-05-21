#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <uiclass/MainWindow.hpp>
#include <utilities/Observer/SdlObserver.h>

class Button: public SdlObserver
{
	private:
		MainWindow *m_parent;
		int m_x;
		int m_y;

	public:
		Button(MainWindow *prnt, int pos_x, int pos_y);
		~Button();
		void onSdlEventReceived(SDL_Event event);
};

#endif