#include <vector>
#include <iostream>
#include <utilities/RessourceManager.h>

using namespace std;

RessourceManager::RessourceManager()
{
	//images_sfc = std::vector<SDL_Surface *>();
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

	m_fontspaths[KremlinFont40] = "ressources/kremlin.ttf";
	m_fontspaths[KremlinFont20] = "ressources/kremlin.ttf";
	m_fontspaths[LatoFont20] = "ressources/lato.ttf";

	m_fonts_size[KremlinFont40] = 40;
	m_fonts_size[KremlinFont20] = 20;
	m_fonts_size[LatoFont20] = 20;
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

int RessourceManager::loadFonts()
{
	for(int i = 0; i < END_OF_FONTS; i++)
	{
		m_fonts.insert(m_fonts.begin() + i, TTF_OpenFont(m_fontspaths[i].c_str(), m_fonts_size[i]));
		if (m_fonts.at(i) == NULL)
		{
			cerr << "error during font initialization "  << m_fontspaths[i] << ", size : " << m_fonts_size[i] << endl;
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

void RessourceManager::unloadFonts()
{
	m_fonts.clear();
}

SDL_Surface *RessourceManager::getSurface(int index)
{
	return images_sfc.at(index);
}

TTF_Font *RessourceManager::getFont(FontEntities font)
{
	return m_fonts.at(font);
}



