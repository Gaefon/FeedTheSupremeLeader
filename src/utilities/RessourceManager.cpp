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
	images_sfc.insert(images_sfc.begin() + RessourceManager::Menu_Background, SDL_LoadBMP("ressources/menu_background.bmp"));
	images_sfc.insert(images_sfc.begin() + RessourceManager::Default_tile, SDL_LoadBMP("ressources/default_tile.bmp"));
	loadBuildings();
	return 0;
}
void RessourceManager::loadButtons()
{
	images_sfc.insert(images_sfc.begin() + RessourceManager::Menu_Default_Button, SDL_LoadBMP("ressources/play_button.bmp"));
	images_sfc.insert(images_sfc.begin() + RessourceManager::Menu_Large_Button, SDL_LoadBMP("ressources/large_button.bmp"));
}

void RessourceManager::loadBuildings()
{
	images_sfc.insert(images_sfc.begin() + RessourceManager::Farm, SDL_LoadBMP("ressources/farm.bmp"));
	images_sfc.insert(images_sfc.begin() + RessourceManager::Button_Menu_Game, SDL_LoadBMP("ressources/btn_menu_game.bmp"));
	images_sfc.insert(images_sfc.begin() + RessourceManager::Button_Menu_Game_Cancel, SDL_LoadBMP("ressources/btn_menu_game_cancel.bmp"));
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



