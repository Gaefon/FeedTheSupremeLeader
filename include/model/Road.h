#ifndef ROAD_HPP
#define ROAD_HPP

#include <string>
#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>

class Road: public Building
{
	private:
		SDL_Texture *m_texture;
		SDL_Rect draw_surface;
		SDL_Color m_map_color;

	public:
		Road(MainWindow* prt);
		~Road();

        bool onVillageUpdateRequest(Village *village);
		void drawBuilding(int rel_x, int rel_y);
		bool isDraggable();
		SDL_Color *getMinimapBuidingColor();
};

#endif
