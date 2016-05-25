#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>

#include <utilities/Poller/SDLPoller.h>

void showMenu(MainWindow *window)
{
	bool request_close = false;
	SDLPoller main_poller;
	Button play_button(window, 0, 40, "ressources/play_button.bmp", "Play");
	Button param_button(window, 0, 100, "ressources/play_button.bmp", "Parameters");
	Button quit_button(window, 0, 160, "ressources/play_button.bmp", "Quit");

	main_poller.subscribe(window);
	main_poller.subscribe(&play_button);
	main_poller.subscribe(&param_button);
	main_poller.subscribe(&quit_button);
	while (!window->hasCloseRequest() && !request_close)
	{
		play_button.setPosition(window->getWidth() / 2 - play_button.getWidth() / 2, 40);
		param_button.setPosition(window->getWidth() / 2 - param_button.getWidth() / 2, 100);
		quit_button.setPosition(window->getWidth() / 2 - quit_button.getWidth() / 2, 160);
		main_poller.Poll();
		window->clear();
		play_button.draw();
		param_button.draw();
		quit_button.draw();
		window->update();
		if (play_button.isClicked())
			showGame(window);
		if (param_button.isClicked())
			showParameters(window);
		if (quit_button.isClicked())
			request_close = true;
		SDL_Delay(20);
	}
}