#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/Button.h>
#include <model/Map.h>

#define WAV_TEST "ressources/sounds/test.wav"

using namespace std;

int main(int argc, char ** argv)
{
	MainWindow window;

	(void) argc;
	(void) argv;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window.displayWindow();
	Sounds *s = new Sounds();
	s->init_audio();
	showMenu(&window);

	TTF_Quit();
	SDL_Quit();
	return 0;
}
