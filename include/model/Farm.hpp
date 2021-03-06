#ifndef FARM_HPP
#define FARM_HPP

#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>

class Farm : public Building
{
	private:
		SDL_Texture *m_texture;
		SDL_Rect draw_surface;
		SDL_Color m_map_color;
		int m_production_rate;
		unsigned int m_max_workers;
		unsigned int m_nb_workers;

	public:
		Farm(MainWindow* prt);
		~Farm();

		int getProductionRate();
		void setProductionRate(int production);
        bool onVillageUpdateRequest(Village *village);
		void drawBuilding(int rel_x, int rel_y);
		SDL_Color *getMinimapBuidingColor();
		unsigned int getPrice();

		unsigned int getMaxWorkers();
		void setMaxWorkers(unsigned int pop);
		unsigned int getWorkers();
		void setWorkers(unsigned int pop);
};

#endif // FARM_HPP
