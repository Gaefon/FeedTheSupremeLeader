#include <utilities/RessourceManager.h>

RessourceManager::RessourceManager()
{
}

int RessourceManager::loadImages()
{
	m_menu_default_button = SDL_LoadBMP("ressources/play_button.bmp");
	m_menu_large_button = SDL_LoadBMP("ressources/large_button.bmp");
	m_menu_background = SDL_LoadBMP("ressources/menu_background.bmp");

	return 0;
}	

void RessourceManager::unloadImages()
{
	SDL_FreeSurface(m_menu_default_button);
	SDL_FreeSurface(m_menu_large_button);
	SDL_FreeSurface(m_menu_background);
}

SDL_Surface *RessourceManager::getMenuDefaultButton()
{
	return m_menu_default_button;
}

SDL_Surface *RessourceManager::getMenuLargeButton()
{
	return m_menu_large_button;
}

SDL_Surface *RessourceManager::getMenuBackground()
{
	return m_menu_background;
}

