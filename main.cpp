#include <iostream>
#include <SDL.h>

#include <uiclass/MainWindow.hpp>
#include <uiclass/Button.h>
#include <model/Map.h>
#include <utilities/Poller/SDLPoller.h>

using namespace std;

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

void showMenu(MainWindow *window, SDLPoller *main_poller)
{
	Button play_button(window, window->getWidth() / 2, 40, "ressources/play_button.bmp");

	main_poller->subscribe(&play_button);
	while (!window->hasCloseRequest())
	{
		main_poller->Poll();
		window->clear();
		play_button.draw();
		window->update();
		if (play_button.isClicked())
			showGame(window, main_poller);
		SDL_Delay(20);
	}
	main_poller->unSubscribe(&play_button);
}

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
		showMenu(&window, &main_poller);
		//showGame(&window, &main_poller);
	}

	SDL_Quit();
	return 0;
}
