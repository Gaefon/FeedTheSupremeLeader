#include <iostream>
#include <SDL.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/GameInterface.h>
#include <uiclass/Button.h>
#include <uiclass/GameMenuDialog.h>
#include <model/Map.h>
#include <utilities/Timer.h>

#include <utilities/Poller/SDLPoller.h>

void showGame(MainWindow *window)
{
	SDLPoller poller;
	GameMenuDialog game_menu(window, &poller, 300, 200);
	GameInterface game_iface(window, &poller);

	poller.subscribe(window);
	poller.subscribe(&game_menu);
	Timer::getInstance()->setLastTime(SDL_GetTicks());
	while (!window->hasCloseRequest() && !game_menu.isGotoMenuRequested())
	{
		poller.Poll();
		window->clear();
		game_iface.draw();
		game_menu.draw();
		window->update();
		Timer::getInstance()->getTimeDifference();
		// SDL_Delay(20);
	}
}
