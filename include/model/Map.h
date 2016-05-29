#ifndef MAP_H
#define MAP_H

#include <list>

#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>
#include <utilities/Observer/SdlObserver.h>

class Map: public SdlObserver
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_margin;

		unsigned int m_display_width;
		unsigned int m_display_height;

		MainWindow *m_parent;

		bool m_is_moving;
		/*int m_previous_x;
		int m_previous_y;*/
		int m_map_relative_position_x;
		int m_map_relative_position_y;

		std::list<Building *> m_list_building;

		void drawMapGrid();
		void checkCursorPosition();

	public:
		Map(MainWindow *par);
		virtual ~Map();

		void setWidth(unsigned int val);
		unsigned int getWidth();
		void setHeight(unsigned int val);
		unsigned int getHeight();

		void setDisplayWidth(int new_w);
		void setDisplayHeight(int new_h);

		void drawMap();

		bool onSdlEventReceived(SDL_Event event);
};

#endif // MAP_H
