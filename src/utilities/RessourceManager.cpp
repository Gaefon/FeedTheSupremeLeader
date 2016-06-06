#include <utilities/RessourceManager.h>
#include <vector>
#include <iostream>
using namespace std;
RessourceManager::RessourceManager()
{
	images_sfc = std::vector<SDL_Surface *>();
	loadAccessPath();
}

void RessourceManager::loadAccessPath()
{
    m_accesspaths[Menu_Background] = "ressources/menu_background.bmp";
    m_accesspaths[Default_tile] = "ressources/default_tile.bmp";
    m_accesspaths[Menu_Default_Button] = "ressources/play_button.bmp";
    m_accesspaths[Menu_Large_Button] = "ressources/large_button.bmp";
    m_accesspaths[Farm] = "ressources/farm.bmp";
    m_accesspaths[Button_Menu_Game] = "ressources/btn_menu_game.bmp";
    m_accesspaths[Button_Menu_Game_Cancel] = "ressources/btn_menu_game_cancel.bmp";
    m_accesspaths[Medium_Slider] = "ressources/medium_slider.bmp";

}

int RessourceManager::loadImages()
{
    for(int i = 0; i < END_OF_ENUM; i++)
    {
        images_sfc.insert(images_sfc.begin() + i, SDL_LoadBMP(m_accesspaths[i].c_str()));
        if (images_sfc.at(i) == NULL)
        {
            cerr << "error during image initialization "  << m_accesspaths[i] << endl;
            return -1;
        }
    }
	return 0;
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



