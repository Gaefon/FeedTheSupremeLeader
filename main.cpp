#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <model/Map.h>
#include <utilities/RessourceManager.h>
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

	if(RessourceManager::getInstance()->loadImages() < 0)
        SDL_Quit();
	Sounds::getInstance()->initMixerAudio();
	Sounds::getInstance()->loadMusic();
	Config::getInstance()->readConfiguration();
	window.displayWindow();
	window.setFullscreen(Config::getInstance()->get(Config::Fullscreen));
	showMenu(&window);

	RessourceManager::getInstance()->unloadImages();
	Sounds::getInstance()->closeMixerAudio();
	TTF_Quit();
	SDL_Quit();
	return 0;
}
