#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <iostream>
#include <SDL.h>
#include <utilities/Observer/VillageObserver.h>
#include <uiclass/MainWindow.hpp>

class Building : public VillageObserver
{
    private:
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_pos_x;
		unsigned int m_pos_y;
		std::string m_name;
		MainWindow *m_parent;

	public:
		Building(MainWindow *prt);
		virtual ~Building();
		unsigned int getWidth();
		unsigned int getDisplayWidth();
		void setWidth(unsigned int val);
		unsigned int getHeight();
		unsigned int getDisplayHeight();
		void setHeight(unsigned int val);

		unsigned int getPosX();
		void setPosX(unsigned int val);
		unsigned int getPosY();
		void setPosY(unsigned int val);

		virtual bool isDraggable();

		std::string getName();
		MainWindow *getParent();
		void setName(std::string val);
		virtual void drawBuilding(int rel_x, int rel_y) = 0;
		virtual SDL_Color *getMinimapBuidingColor() = 0;
		virtual bool onVillageUpdateRequest(Village *village) = 0;

		virtual unsigned int hasMaxOccupancy();
};

#endif // BUILDING_HPP
