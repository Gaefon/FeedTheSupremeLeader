#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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
			Button_School_Game,
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

		enum SoundEntities
		{
			BuildingBuild = 0,
			BuildingDestroy,
			MenuClick,
			END_OF_SOUNDS
		};

		int loadImages();
		int loadFonts();
		int loadSounds();
		void unloadImages();
		void unloadFonts();
		void unloadSounds();

		SDL_Surface *getSurface(int index);
		TTF_Font *getFont(FontEntities font);
		Mix_Chunk *getSound(SoundEntities snd);

	private:
		std::vector<SDL_Surface *> images_sfc;
		std::vector<TTF_Font *> m_fonts;
		std::vector<Mix_Chunk *> m_sounds;

		std::string m_accesspaths[END_OF_ENUM];
		std::string m_fontspaths[END_OF_FONTS];
		int m_fonts_size[END_OF_FONTS];
		std::string m_sounds_paths[END_OF_SOUNDS];
		RessourceManager();
		void loadAccessPath();

};

#endif
