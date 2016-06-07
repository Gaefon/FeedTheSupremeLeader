#include <Constants.hpp>
#include <iostream>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <uiclass/Slider.h>
#include <utilities/Config.h>
#include <SDL.h>
#include <utilities/Timer.h>
#include <utilities/sounds/sounds.h>

#include <utilities/RessourceManager.h>
#include <utilities/Poller/SDLPoller.h>

using namespace std;

string getButtonString()
{
	if (Config::getInstance()->get(Config::Fullscreen))
		return "Fullscreen : On";
	return "Fullscreen : Off";
}

string getMusicButtonString()
{
	if (!Config::getInstance()->getMusic())
		return "Music : On";
	else
		return "Music : Off";
}

void toggleMusic(Button *btn_audio)
{
	cout << Config::getInstance()->getMusic() << endl;
	if (Config::getInstance()->getMusic())	{
			// cout << "Pause" << endl;
			Sounds::getInstance()->pauseMusic();
	} else {
			// cout << "Resume" << endl;
			Sounds::getInstance()->resumeMusic();
	}
	Config::getInstance()->setMusic(!Config::getInstance()->getMusic());
	btn_audio->setText(getMusicButtonString());
}

void toggleFullscreen(MainWindow *window, Button *btn_fullscreen)
{
	Config::getInstance()->set(Config::Fullscreen, !Config::getInstance()->get(Config::Fullscreen));
	btn_fullscreen->setText(getButtonString());
	window->setFullscreen(Config::getInstance()->get(Config::Fullscreen));
}

void showParameters(MainWindow *window)
{
	SDLPoller poller;
	bool back_clicked = false;
	SDL_Texture *m_button_texture = SDL_CreateTextureFromSurface(window->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Background));
	Button back_button(window, 10, 10, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Default_Button), "Back");
	Button btn_fullscreen(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Large_Button), getButtonString());
	Button btn_audio(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Large_Button), getMusicButtonString());
	Slider slider_test(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Medium_Slider));

	//poller.subscribe(&slider_test);
	poller.subscribe(&back_button);
	poller.subscribe(&btn_fullscreen);
	poller.subscribe(&btn_audio);
	poller.subscribe(window);

	Timer::getInstance()->setLastTime(SDL_GetTicks());
	while (!window->hasCloseRequest() && !back_clicked)
	{
		btn_fullscreen.setPosition(window->getWidth() / 2 - btn_fullscreen.getWidth() / 2, 80);
		btn_audio.setPosition(window->getWidth() / 2 - btn_fullscreen.getWidth() / 2, 140);

		poller.Poll();
		window->clear();
		window->setBackground(m_button_texture);
		back_button.draw();
		btn_fullscreen.draw();
		btn_audio.draw();
		//slider_test.draw();
		window->update();
		if (back_button.isClicked()) {
			back_clicked = true;
			Config::getInstance()->saveConfiguration();
		}
		if (btn_fullscreen.isClicked())
			toggleFullscreen(window, &btn_fullscreen);
		if (btn_audio.isClicked()) {
			toggleMusic(&btn_audio);
		}
		// SDL_Delay(20);
		Timer::getInstance()->getTimeDifference();
	}
}
