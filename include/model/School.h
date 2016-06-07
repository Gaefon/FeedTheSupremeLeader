#ifndef SCHOOL_HPP
#define SCHOOL_HPP

#include <string>
#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>

class School : public Building
{
	private:
		SDL_Texture *m_texture;
		SDL_Rect draw_surface;
		SDL_Color m_map_color;

	public:
		School(MainWindow* prt);
		~School();

		void drawBuilding(int rel_x, int rel_y);
		SDL_Color *getMinimapBuidingColor();
};

#endif
