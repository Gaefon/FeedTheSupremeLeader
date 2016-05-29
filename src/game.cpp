#include <iostream>
#include <SDL.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/GameInterface.h>
#include <uiclass/Button.h>
#include <model/Map.h>

#include <utilities/Poller/SDLPoller.h>

void showGame(MainWindow *window)
{
	SDLPoller poller;
	GameInterface game_iface(window, &poller);
	//Map map(window);

	//poller.subscribe(&map);
	poller.subscribe(window);
	while (!window->hasCloseRequest())
	{
		poller.Poll();
		window->clear();
		//map.drawMap();
		game_iface.draw();
		window->update();
		SDL_Delay(20);
	}
}