#ifndef GAME_MENU_DIALOG_H
#define GAME_MENU_DIALOG_H

#include <uiclass/Widget.h>
#include <utilities/Observer/SdlObserver.h>

class GameMenuDialog: public Widget, public SdlObserver
{
	private:
		int m_width;
		int m_height;
		bool m_is_visible;

	public:
		GameMenuDialog(MainWindow *parent, int w, int h);
		~GameMenuDialog();
		int getWidth();
		int getHeight();
		void draw();
		void onSdlEventReceived(SDL_Event event);
}

#endif