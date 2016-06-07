#include <Constants.hpp>
#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <uiclass/Label.h>
#include <utilities/RessourceManager.h>
#include <SDL.h>
#include <utilities/Timer.h>
#include <utilities/sounds/sounds.h>

#include <utilities/Poller/SDLPoller.h>

void showMenu(MainWindow *window)
{
	bool request_close = false;
	SDLPoller main_poller;
	Label title_label(window, 0, 0, GAME_NAME);
	SDL_Texture *m_bg_texture = SDL_CreateTextureFromSurface(window->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Background));
	Button play_button(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Default_Button), "Play");
	Button param_button(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Default_Button), "Parameters");
	Button quit_button(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Default_Button), "Quit");

	title_label.setFont(RessourceManager::KremlinFont40);
	main_poller.subscribe(window);
	main_poller.subscribe(&play_button);
	main_poller.subscribe(&param_button);
	main_poller.subscribe(&quit_button);
	Timer::getInstance()->setLastTime(SDL_GetTicks());
	while (!window->hasCloseRequest() && !request_close)
	{
		title_label.setPosition(window->getWidth() / 2 - title_label.getWidth() / 2, 40);
		play_button.setPosition(window->getWidth() / 2 - play_button.getWidth() / 2, 160);
		param_button.setPosition(window->getWidth() / 2 - param_button.getWidth() / 2, 220);
		quit_button.setPosition(window->getWidth() / 2 - quit_button.getWidth() / 2, 280);
		main_poller.Poll();
		window->clear();
		window->setBackground(m_bg_texture);
		title_label.draw();
		play_button.draw();
		param_button.draw();
		quit_button.draw();
		window->update();
		if (play_button.isClicked()) {
			Sounds::getInstance()->loadWav(MENU_CLICK_WAV);
			Sounds::getInstance()->pauseMusic();
			showGame(window);
		}
		if (param_button.isClicked()) {
				Sounds::getInstance()->loadWav(MENU_CLICK_WAV);
				showParameters(window);
		}
		if (quit_button.isClicked())
			request_close = true;
		// SDL_Delay(20);
		Timer::getInstance()->getTimeDifference();
	}
}
