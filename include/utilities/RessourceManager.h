#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <vector>
#include <string>
#include <SDL.h>
#include <utilities/Singleton.hpp>

class RessourceManager: public Singleton<RessourceManager>
{
	friend class Singleton<RessourceManager>;

	public:
        enum DrawableEntities
        {
            Menu_Default_Button = 0,
            Menu_Large_Button = 1,
            Menu_Background = 2,
            Default_tile = 3,
            Farm = 4,
            Button_Menu_Game = 5,
            Button_Menu_Game_Cancel = 6,
            END_OF_ENUM = 7,
        };
		int loadImages();
		void unloadImages();

		SDL_Surface *getSurface(int index);

	private:
		std::vector<SDL_Surface *> images_sfc;
		std::string m_accesspaths[END_OF_ENUM];
		RessourceManager();
		void loadAccessPath();

};

#endif
