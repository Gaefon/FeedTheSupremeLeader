#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include <utilities/Singleton.hpp>

class RessourceManager: public Singleton<RessourceManager>
{
	friend class Singleton<RessourceManager>;

	public:
		enum DrawableEntities
		{
			Menu_Default_Button = 0,
			Menu_Large_Button,
			Menu_Background,
			BackgroundMenuMap,
			BackgroundMenuButton,
			Default_tile,
			Farm,
			House,
			School,
			Road,
			Button_Menu_Game,
			Button_Menu_Game_Cancel,
			Medium_Slider,
			Counter_bg,
			END_OF_ENUM
		};

		enum FontEntities
		{
			KremlinFont40 = 0,
			KremlinFont20,
			LatoFont20,
			END_OF_FONTS
		};
		int loadImages();
		int loadFonts();
		void unloadImages();
		void unloadFonts();

		SDL_Surface *getSurface(int index);
		TTF_Font *getFont(FontEntities font);

	private:
		std::vector<SDL_Surface *> images_sfc;
		std::vector<TTF_Font *> m_fonts;

		std::string m_accesspaths[END_OF_ENUM];
		std::string m_fontspaths[END_OF_FONTS];
		int m_fonts_size[END_OF_FONTS];
		RessourceManager();
		void loadAccessPath();

};

#endif
