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

	public:
		Farm(MainWindow* prt);
		~Farm();

		void drawBuilding(int rel_x, int rel_y);
		std::string getName();
		SDL_Color *getMinimapBuidingColor();
};

#endif // FARM_HPP
