#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <string>
#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>

class House : public Building
{
	private:
		SDL_Texture *m_texture;
		SDL_Rect draw_surface;
		SDL_Color m_map_color;

	public:
		House(MainWindow* prt);
		~House();

        bool onVillageUpdateRequest(Village *village);
		void drawBuilding(int rel_x, int rel_y);
		SDL_Color *getMinimapBuidingColor();
};

#endif
