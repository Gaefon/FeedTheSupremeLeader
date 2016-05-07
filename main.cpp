#include <iostream>
#include <SDL.h>

#include <uiclass/MainWindow.hpp>

using namespace std;

int main(void)
{
	MainWindow window;

	SDL_Init(SDL_INIT_VIDEO);

	window.displayWindow();
	while (1)
	{
	}

	SDL_Quit();
	return 0;
}
