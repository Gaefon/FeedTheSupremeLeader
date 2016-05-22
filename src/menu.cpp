#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>

void showMenu(MainWindow *window, SDLPoller *main_poller)
{
	Button play_button(window, 0, 40, "ressources/play_button.bmp", "Play");
	Button param_button(window, 0, 100, "ressources/play_button.bmp", "Parameters");

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