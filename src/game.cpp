#include <iostream>
#include <SDL.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/GameInterface.h>
#include <uiclass/Button.h>
#include <uiclass/GameMenuDialog.h>
#include <model/Map.h>
#include <utilities/timer.h>

#include <utilities/Poller/SDLPoller.h>
#include <model/Village.h>

void showGame(MainWindow *window)
{
	SDLPoller poller;
	VillagePoller village_poller;
	GameMenuDialog game_menu(window, &poller, 300, 200);
	GameInterface game_iface(window, &poller, &village_poller);

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
