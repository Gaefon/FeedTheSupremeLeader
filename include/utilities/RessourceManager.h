#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <SDL.h>
#include <utilities/Singleton.hpp>

class RessourceManager: public Singleton<RessourceManager>
{
	friend class Singleton<RessourceManager>;

	private:
		RessourceManager();
		SDL_Surface *m_menu_default_button;
		SDL_Surface *m_menu_large_button;
		SDL_Surface *m_menu_background;

	public:
		int loadImages();
		void unloadImages();
		SDL_Surface *getMenuDefaultButton();
		SDL_Surface *getMenuLargeButton();
		SDL_Surface *getMenuBackground();
};

#endif