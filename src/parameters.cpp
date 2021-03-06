#include <Constants.hpp>
#include <iostream>
#include <math.h>
#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <uiclass/Slider.h>
#include <uiclass/Label.h>
#include <utilities/Config.h>
#include <SDL.h>
#include <utilities/Timer.h>
#include <utilities/sounds/sounds.h>

#include <utilities/RessourceManager.h>
#include <utilities/Poller/SDLPoller.h>

using namespace std;

string getButtonString()
{
	if (Config::getInstance()->getBool(Config::Fullscreen))
		return "Fullscreen : On";
	return "Fullscreen : Off";
}

string getMusicButtonString()
{
	if (!Config::getInstance()->getBool(Config::Music))
		return "Music : Off";
	return "Music : On";
}

string getSoundsEffectButtonString()
{
	if (!Config::getInstance()->getBool(Config::SoundsEffects))
		return "Sounds effects : Off";
	return "Sounds effects : On";
}

void toggleMusic(Button *btn_audio)
{
	if (Config::getInstance()->getBool(Config::Music))
		Sounds::getInstance()->pauseMusic();
	else
		Sounds::getInstance()->resumeMusic();
	Config::getInstance()->set(Config::Music, !Config::getInstance()->getBool(Config::Music));
	btn_audio->setText(getMusicButtonString());
}

void toggleSoundsEffects(Button *btn)
{
	Config::getInstance()->set(Config::SoundsEffects, !Config::getInstance()->getBool(Config::SoundsEffects));
	btn->setText(getSoundsEffectButtonString());
}

void toggleFullscreen(MainWindow *window, Button *btn_fullscreen)
{
	Config::getInstance()->set(Config::Fullscreen, !Config::getInstance()->getBool(Config::Fullscreen));
	btn_fullscreen->setText(getButtonString());
	window->setFullscreen(Config::getInstance()->getBool(Config::Fullscreen));
}

void setMapSensivity(Slider *slider)
{
	int sensivity = roundf((slider->getValue() * (MAX_MAP_SENSIVITY - MIN_MAP_SENSIVITY)) / 100.0f) + MIN_MAP_SENSIVITY;
	Config::getInstance()->set(Config::MapSensivity, sensivity);
}

void setAudioVolume(Slider *slider) {
	int volume = int((slider->getValue() * MIX_MAX_VOLUME) / 100);
	Config::getInstance()->set(Config::AudioVolume, volume);
	Sounds::getInstance()->setMusicVolume(volume);
}

void showParameters(MainWindow *window)
{
	SDLPoller poller;
	bool back_clicked = false;
	SDL_Texture *m_button_texture = SDL_CreateTextureFromSurface(window->getRenderer(), RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Background));
	Button back_button(window, 10, 10, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Default_Button), "Back");
	Button btn_fullscreen(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Large_Button), getButtonString());
	Button btn_audio(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Large_Button), getMusicButtonString());
	Label lbl_map(window, 0, 0, "Map sensivity");
	Slider slider_map_sensivity(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Medium_Slider));
	Label lbl_audio(window, 0, 0, "Volume");
	Slider slider_audio(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Medium_Slider));
	Label lbl_sound_effects(window, 0, 0, "Sounds effects");
	Button btn_sound_effects(window, 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Large_Button), getSoundsEffectButtonString());


	slider_map_sensivity.setValue(roundf(((Config::getInstance()->getInt(Config::MapSensivity) - MIN_MAP_SENSIVITY) * 100.0f) / (MAX_MAP_SENSIVITY - MIN_MAP_SENSIVITY)));
	slider_audio.setValue(Config::getInstance()->getInt(Config::AudioVolume) * 100 / 128);
	poller.subscribe(&back_button);
	poller.subscribe(&btn_fullscreen);
	poller.subscribe(&btn_audio);
	poller.subscribe(&slider_audio);
	poller.subscribe(&slider_map_sensivity);
	poller.subscribe(&btn_sound_effects);
	poller.subscribe(window);

	Timer::getInstance()->setLastTime(SDL_GetTicks());
	while (!window->hasCloseRequest() && !back_clicked)
	{
		btn_fullscreen.setPosition(window->getWidth() / 2 - btn_fullscreen.getWidth() / 2, 80);
		lbl_map.setPosition(window->getWidth() / 2 - lbl_map.getWidth() / 2, 140);
		slider_map_sensivity.setPosition(window->getWidth() / 2 - slider_map_sensivity.getWidth() / 2, 170);	
		lbl_audio.setPosition(window->getWidth() / 2 - lbl_audio.getWidth() / 2, 214);
		btn_audio.setPosition(window->getWidth() / 2 - btn_fullscreen.getWidth() / 2, 244);
		slider_audio.setPosition(window->getWidth() / 2 - slider_audio.getWidth() / 2, 294);
		lbl_sound_effects.setPosition(window->getWidth() / 2 - lbl_sound_effects.getWidth() / 2, 338);
		btn_sound_effects.setPosition(window->getWidth() / 2 - btn_sound_effects.getWidth() / 2, 368);

		poller.Poll();
		window->clear();
		window->setBackground(m_button_texture);
		back_button.draw();
		btn_fullscreen.draw();
		btn_audio.draw();
		slider_map_sensivity.draw();
		lbl_audio.draw();
		slider_audio.draw();
		lbl_map.draw();
		lbl_sound_effects.draw();
		btn_sound_effects.draw();

		window->update();
		if (back_button.isClicked())
		{
			back_clicked = true;
			Config::getInstance()->saveConfiguration();
		}
		if (btn_fullscreen.isClicked())
			toggleFullscreen(window, &btn_fullscreen);
		if (btn_audio.isClicked())
			toggleMusic(&btn_audio);
		if (slider_map_sensivity.slideFinished())
			setMapSensivity(&slider_map_sensivity);

		if (slider_audio.slideFinished())
			setAudioVolume(&slider_audio);
		if (btn_sound_effects.isClicked())
			toggleSoundsEffects(&btn_sound_effects);
		Timer::getInstance()->getTimeDifference();
	}
}
