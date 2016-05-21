#include <iostream>
#include <SDL.h>

#include <uiclass/MainWindow.hpp>
#include <model/Map.h>
#include <utilities/Poller/SDLPoller.h>

using namespace std;

int main(int argc, char ** argv)
{
	MainWindow window;
	Map map(&window);
	SDLPoller main_poller;

	(void) argc;
	(void) argv;

	SDL_Init(SDL_INIT_VIDEO);

	window.displayWindow();
	main_poller.subscribe(&window);
	main_poller.subscribe(&map);
	while (!window.hasCloseRequest())
	{
		main_poller.Poll();
		window.clear();
		map.drawMap();
		window.update();
		SDL_Delay(20);
	}

	SDL_Quit();
	return 0;
}
