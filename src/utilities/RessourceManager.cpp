#include <utilities/RessourceManager.h>
#include <vector>
#include <iostream>
RessourceManager::RessourceManager()
{
	images_sfc = std::vector<SDL_Surface *>();
}

int RessourceManager::loadImages()
{
	loadButtons();
	images_sfc.push_back(SDL_LoadBMP("ressources/menu_background.bmp"));
	loadBuildings();
	return 0;
}
void RessourceManager::loadButtons()
{
	images_sfc.push_back(SDL_LoadBMP("ressources/play_button.bmp"));
	images_sfc.push_back(SDL_LoadBMP("ressources/large_button.bmp"));
}

void RessourceManager::loadBuildings()
{
	images_sfc.push_back(SDL_LoadBMP("ressources/farm.bmp"));
	images_sfc.push_back(SDL_LoadBMP("ressources/btn_menu_game.bmp"));
	images_sfc.push_back(SDL_LoadBMP("ressources/btn_menu_game_cancel.bmp"));
}
void RessourceManager::unloadImages()
{
	std::vector<SDL_Surface *>::iterator it;
	// faut pas oublier de faire les appel a SDL_FreeSurface;
	images_sfc.clear();
}

SDL_Surface *RessourceManager::getSurface(int index)
{
	return images_sfc.at(index);
}



