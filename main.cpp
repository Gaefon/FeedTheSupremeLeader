#include <iostream>
#include <SDL.h>

#include <uiclass/MainWindow.hpp>
#include <utilities/Poller/SDLPoller.h>

using namespace std;

int main(int argc, char ** argv)
{
	MainWindow window;
	SDLPoller main_poller;

	(void) argc;
	(void) argv;

	SDL_Init(SDL_INIT_VIDEO);

	window.displayWindow();
	main_poller.subscribe(&window);
	while (!window.hasCloseRequest())
	{
		main_poller.Poll();
		SDL_Delay(20);
	}

	SDL_Quit();
	return 0;
}
