#include <iostream>
#include <SDL.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <model/Map.h>

void showGame(MainWindow *window, SDLPoller *main_poller)
{
	Map map(window);

	main_poller->subscribe(&map);
	while (!window->hasCloseRequest())
	{
		main_poller->Poll();
		window->clear();
		map.drawMap();
		window->update();
		SDL_Delay(20);
	}
	main_poller->unSubscribe(&map);
}