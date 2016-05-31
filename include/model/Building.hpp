#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <iostream>
#include <uiclass/MainWindow.hpp>

class Building
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		std::string m_name;
		MainWindow *m_parent;
		SDL_Texture *m_texture;

	public:
        Building();
		Building(MainWindow *prt);
		virtual ~Building();
		unsigned int getWidth();
		void setWidth(unsigned int val);
		unsigned int getHeight();
		void setHeight(unsigned int val);
		std::string getName();
		MainWindow *getParent();
		void setName(std::string val);
		virtual void drawBuilding();
};

#endif // BUILDING_HPP
