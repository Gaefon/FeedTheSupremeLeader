#include <iostream>
#include <SDL.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <model/Map.h>

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
	Button play_button(window, 0, 40, "ressources/play_button.bmp");
	Button param_button(window, 0, 100, "ressources/play_button.bmp");

	play_button.setPosition(window->getWidth() / 2 - play_button.getWidth() / 2, 40);
	param_button.setPosition(window->getWidth() / 2 - play_button.getWidth() / 2, 100);
	main_poller->subscribe(&play_button);
	main_poller->subscribe(&param_button);
	while (!window->hasCloseRequest())
	{
		main_poller->Poll();
		window->clear();
		play_button.draw();
		param_button.draw();
		window->update();
		if (play_button.isClicked())
			showGame(window, main_poller);
		if (param_button.isClicked())
			showParameters(window, main_poller);
		SDL_Delay(20);
	}
	main_poller->unSubscribe(&play_button);
	main_poller->unSubscribe(&param_button);
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
