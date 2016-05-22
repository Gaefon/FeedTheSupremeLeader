#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>

void showParameters(MainWindow *window, SDLPoller *main_poller)
{
	bool back_clicked = false;
	Button back_button(window, 10, 10, "ressources/play_button.bmp", "Back");
	
	main_poller->subscribe(&back_button);
	while (!window->hasCloseRequest() && !back_clicked)
	{
		main_poller->Poll();
		window->clear();
		back_button.draw();
		window->update();
		if (back_button.isClicked())
			back_clicked = true;
		SDL_Delay(20);
	}
	main_poller->unSubscribe(&back_button);
}