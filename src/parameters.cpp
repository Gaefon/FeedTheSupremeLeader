#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>

void showParameters(MainWindow *window)
{
	SDLPoller poller;
	bool back_clicked = false;
	Button back_button(window, 10, 10, "ressources/play_button.bmp", "Back");
	Button btn_fullscreen(window, 0, 0, "ressources/large_button.bmp", "Fullscreen : Off");
	
	btn_fullscreen.setPosition(window->getWidth() / 2 - btn_fullscreen.getWidth() / 2, 80);

	poller.subscribe(&back_button);
	poller.subscribe(&btn_fullscreen);
	poller.subscribe(window);
	while (!window->hasCloseRequest() && !back_clicked)
	{
		poller.Poll();
		window->clear();
		back_button.draw();
		btn_fullscreen.draw();
		window->update();
		if (back_button.isClicked())
			back_clicked = true;
		SDL_Delay(20);
	}
}