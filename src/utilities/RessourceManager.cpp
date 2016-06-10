#include <vector>
#include <iostream>
#include <utilities/RessourceManager.h>
#include <Constants.hpp>

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
	m_accesspaths[BackgroundMenuMap] = "ressources/background_menu_map.bmp";
	m_accesspaths[BackgroundMenuButton] = "ressources/background_menu_button.bmp";
	m_accesspaths[Farm] = "ressources/farm.bmp";
	m_accesspaths[House] = "ressources/house.bmp";
	m_accesspaths[School] = "ressources/school.bmp";
	m_accesspaths[Road] = "ressources/road.bmp";
	m_accesspaths[Button_Menu_Game] = "ressources/btn_menu_game.bmp";
	m_accesspaths[Button_School_Game] = "ressources/school_button.bmp";
	m_accesspaths[Button_Menu_Game_Cancel] = "ressources/btn_menu_game_cancel.bmp";
	m_accesspaths[Medium_Slider] = "ressources/slider.bmp";
    m_accesspaths[Counter_bg] = "ressources/counterbg.bmp";
    m_accesspaths[Commissar] = "ressources/commissar.bmp";

	m_fontspaths[KremlinFont40] = "ressources/kremlin.ttf";
	m_fontspaths[KremlinFont20] = "ressources/kremlin.ttf";
	m_fontspaths[LatoFont20] = "ressources/lato.ttf";

	m_fonts_size[KremlinFont40] = 40;
	m_fonts_size[KremlinFont20] = 20;
	m_fonts_size[LatoFont20] = 20;

	m_sounds_paths[BuildingBuild] = SOUND_BUILDING_BUILD;
	m_sounds_paths[BuildingDestroy] = SOUND_BUILDING_DESTROY;
	m_sounds_paths[MenuClick] = SOUND_MENU_SELECT;
}

int RessourceManager::loadImages()
{
	for(int i = 0; i < END_OF_ENUM; i++)
	{
		images_sfc.insert(images_sfc.begin() + i, SDL_LoadBMP(m_accesspaths[i].c_str()));
		if (images_sfc.at(i) == NULL)
		{
			cerr << "error during image initialization " << m_accesspaths[i] << endl;
			return -1;
		}
		SDL_SetColorKey(images_sfc.at(i), SDL_TRUE, SDL_MapRGB(images_sfc.at(i)->format, 0xff, 0x00, 0xff));
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

int RessourceManager::loadSounds()
{
	for (int i = 0; i < END_OF_SOUNDS; i++)
	{
		m_sounds.insert(m_sounds.begin() + i, Mix_LoadWAV(m_sounds_paths[i].c_str()));
		if (m_sounds.at(i) == NULL)
		{
			cerr << "error during sound initialization : "  << m_sounds_paths[i] << endl;
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

void RessourceManager::unloadSounds()
{
	m_sounds.clear();
}

SDL_Surface *RessourceManager::getSurface(int index)
{
	return images_sfc.at(index);
}

TTF_Font *RessourceManager::getFont(FontEntities font)
{
	return m_fonts.at(font);
}

Mix_Chunk *RessourceManager::getSound(SoundEntities snd)
{
	return m_sounds.at(snd);
}
