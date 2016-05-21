#ifndef MAP_H
#define MAP_H

#include <uiclass/MainWindow.hpp>

class Map
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		MainWindow *m_parent;

		void drawMapGrid();

	public:
		Map(MainWindow *par);
		virtual ~Map();

		void setWidth(unsigned int val);
		unsigned int getWidth();
		void setHeight(unsigned int val);
		unsigned int getHeight();

		void drawMap();
};

#endif // MAP_H
