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
        unsigned int m_occupancy;
        unsigned int m_max_occupancy;
	public:
		House(MainWindow* prt);
		~House();

		unsigned int getOccupancy();
		void setOccupancy(unsigned int occupancy);
		unsigned int getMaxOccupancy();
		void setMaxOccupancy(unsigned int max_occupancy);
		void drawBuilding(int rel_x, int rel_y);
		SDL_Color *getMinimapBuidingColor();
		unsigned int getPrice();
		
		bool onVillageUpdateRequest(Village *village);
		unsigned int hasMaxOccupancy();
};

#endif
