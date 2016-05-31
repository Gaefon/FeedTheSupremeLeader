#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <vector>
#include <SDL.h>
#include <utilities/Singleton.hpp>

class RessourceManager: public Singleton<RessourceManager>
{
	friend class Singleton<RessourceManager>;

	private:
		RessourceManager();
		std::vector<SDL_Surface *> images_sfc;
		SDL_Surface *m_menu_default_button;
		SDL_Surface *m_menu_large_button;
		SDL_Surface *m_menu_background;
        void loadButtons();
        void loadBuildings();

	public:
		int loadImages();
		void unloadImages();

		SDL_Surface *getSurface(int index);

};

#endif
