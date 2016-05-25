#include <iostream>
#include <SDL.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <model/Map.h>

#include <utilities/Poller/SDLPoller.h>

void showGame(MainWindow *window)
{
	SDLPoller poller;
	Map map(window);

	poller.subscribe(&map);
	poller.subscribe(window);
	while (!window->hasCloseRequest())
	{
		poller.Poll();
		window->clear();
		map.drawMap();
		window->update();
		SDL_Delay(20);
	}
}