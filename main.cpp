#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <model/Map.h>
#include <utilities/RessourceManager.h>

using namespace std;

int main(int argc, char ** argv)
{
	MainWindow window;

	(void) argc;
	(void) argv;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	RessourceManager::getInstance()->loadImages();
	
	window.displayWindow();
	showMenu(&window);

	RessourceManager::getInstance()->unloadImages();

	TTF_Quit();
	SDL_Quit();
	return 0;
}
