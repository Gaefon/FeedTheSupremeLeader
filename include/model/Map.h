#ifndef MAP_H
#define MAP_H

#include <uiclass/MainWindow.hpp>
#include <utilities/Observer/SdlObserver.h>

class Map: public SdlObserver
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		MainWindow *m_parent;

		bool m_is_moving;
		int m_previous_x;
		int m_previous_y;
		int m_map_relative_position_x;
		int m_map_relative_position_y;


		void drawMapGrid();

	public:
		Map(MainWindow *par);
		virtual ~Map();

		void setWidth(unsigned int val);
		unsigned int getWidth();
		void setHeight(unsigned int val);
		unsigned int getHeight();

		void drawMap();

		void onSdlEventReceived(SDL_Event event);
};

#endif // MAP_H
