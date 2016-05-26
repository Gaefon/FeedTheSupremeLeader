#include <iostream>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <utilities/Config.h>

#include <utilities/RessourceManager.h>
#include <utilities/Poller/SDLPoller.h>

using namespace std;

string getButtonString()
{
	if (Config::getInstance()->getFullscreen())
		return "Fullscreen : On";
	return "Fullscreen : Off";
}

void toggleFullscreen(MainWindow *window, Button *btn_fullscreen)
{
	Config::getInstance()->setFullscreen(!Config::getInstance()->getFullscreen());
	btn_fullscreen->setText(getButtonString());
	window->setFullscreen(Config::getInstance()->getFullscreen());
}


void showParameters(MainWindow *window)
{
	SDLPoller poller;
	bool back_clicked = false;
	Button back_button(window, 10, 10, RessourceManager::getInstance()->getMenuDefaultButton(), "Back");
	Button btn_fullscreen(window, 0, 0, RessourceManager::getInstance()->getMenuLargeButton(), getButtonString());

	poller.subscribe(&back_button);
	poller.subscribe(&btn_fullscreen);
	poller.subscribe(window);
	while (!window->hasCloseRequest() && !back_clicked)
	{
		btn_fullscreen.setPosition(window->getWidth() / 2 - btn_fullscreen.getWidth() / 2, 80);

		poller.Poll();
		window->clear();
		back_button.draw();
		btn_fullscreen.draw();
		window->update();
		if (back_button.isClicked())
			back_clicked = true;
		if (btn_fullscreen.isClicked())
			toggleFullscreen(window, &btn_fullscreen);
		SDL_Delay(20);
	}
}