#ifndef GAME_MENU_DIALOG_H
#define GAME_MENU_DIALOG_H

#include <uiclass/Widget.h>
#include <uiclass/Button.h>
#include <uiclass/GameInterface.h>
#include <utilities/Poller/SDLPoller.h>
#include <utilities/Observer/SdlObserver.h>


class GameMenuDialog: public Widget, public SdlObserver
{
	private:
		int m_width;
		int m_height;
		SDL_Rect rect_back;
		bool m_is_visible;
		bool m_is_goto_menu_requested;
		Button *m_btn_menu;
		SDLPoller *m_poller;
		GameInterface *m_iface;

		void registerButtons();
		void unregisterButton();

	public:
		GameMenuDialog(MainWindow *parent, GameInterface *iface, SDLPoller *poller, int w, int h);
		~GameMenuDialog();
		int getWidth();
		int getHeight();
		bool isGotoMenuRequested();
		void draw();
		bool onSdlEventReceived(SDL_Event event);
};

#endif