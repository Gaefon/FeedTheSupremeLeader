#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <FeedTheSupremLeader.h>
#include <utilities/RessourceManager.h>
#include <Constants.hpp>
#include <utilities/Config.h>
#include <utilities/sounds/sounds.h>

using namespace std;
int main(int argc, char ** argv)
{
	MainWindow window;

	(void) argc;
	(void) argv;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	Sounds::getInstance()->initMixerAudio();

	if(RessourceManager::getInstance()->loadImages() < 0)
	{
		SDL_Quit();
		return EXIT_FAILURE;
	}

	if(RessourceManager::getInstance()->loadFonts() < 0)
	{
		SDL_Quit();
		return EXIT_FAILURE;
	}

	if (RessourceManager::getInstance()->loadSounds() < 0)
	{
		SDL_Quit();
		return EXIT_FAILURE;
	}

	Config::getInstance()->readConfiguration();
	Sounds::getInstance()->loadMusic(MENU_MUSIQUE);
	Sounds::getInstance()->setMusicVolume(Config::getInstance()->getInt(Config::AudioVolume));
	if (!Config::getInstance()->getBool(Config::Music))
		Sounds::getInstance()->pauseMusic();
	window.displayWindow();
	window.setFullscreen(Config::getInstance()->getBool(Config::Fullscreen));
	showMenu(&window);

	RessourceManager::getInstance()->unloadImages();
	RessourceManager::getInstance()->unloadFonts();
	RessourceManager::getInstance()->unloadSounds();
	Sounds::getInstance()->closeMixerAudio();
	TTF_Quit();
	SDL_Quit();
	return 0;
}
