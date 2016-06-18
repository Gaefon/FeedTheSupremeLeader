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
		unsigned int m_occupancy;
		unsigned int m_max_occupancy;

	public:
		School(MainWindow* prt);
		~School();

        bool onVillageUpdateRequest(Village *village);
		void drawBuilding(int rel_x, int rel_y);
		SDL_Color *getMinimapBuidingColor();
		unsigned int getPrice();
		
        unsigned int getOccupancy();
        void setOccupancy(unsigned int occupancy);
        unsigned int getMaxOccupancy();
        void setMaxOccupancy(unsigned int occupancy);
        unsigned int hasMaxOccupancy();
};

#endif
