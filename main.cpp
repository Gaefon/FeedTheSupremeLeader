#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <model/Map.h>

using namespace std;

int main(int argc, char ** argv)
{
	MainWindow window;
	SDLPoller main_poller;

	(void) argc;
	(void) argv;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	window.displayWindow();
	main_poller.subscribe(&window);
	
	showMenu(&window, &main_poller);

	TTF_Quit();
	SDL_Quit();
	return 0;
}
