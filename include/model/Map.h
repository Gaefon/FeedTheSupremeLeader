#ifndef MAP_H
#define MAP_H

#include <list>
#include <SDL.h>

#include <model/Building.hpp>
#include <uiclass/MainWindow.hpp>
#include <utilities/Observer/SdlObserver.h>

#include <utilities/Poller/MapPoller.h>

class Map: public SdlObserver
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_margin;

		unsigned int m_display_width;
		unsigned int m_display_height;

		int m_move_sensivity;

		MainWindow *m_parent;

		bool m_is_moving;
		int m_map_relative_position_x;
		int m_map_relative_position_y;

		std::list<Building *> m_list_building;
		Building *m_tmp_building;

		SDL_Texture *m_texture_tile;
		SDL_Rect draw_tile_surface;
		SDL_Rect m_map_surface;

		MapPoller m_poller;

		void drawMapGrid();
		void checkCursorPosition();
		// Building * getCopyOfTmpBuilding(Building *tmp_building);

	public:
		Map(MainWindow *par);
		virtual ~Map();

		void setWidth(unsigned int val);
		unsigned int getWidth();
		void setHeight(unsigned int val);
		unsigned int getHeight();

		void setDisplayWidth(int new_w);
		void setDisplayHeight(int new_h);

		int getTilePosX();
		int getTilePosY();
		void setTileMapPos(int pos_x, int pos_y);

		void setTmpBuilding(Building *tmp);
		std::list<Building *> *getBuildings();

		MapPoller *getPoller();

		void drawMap();

		bool onSdlEventReceived(SDL_Event event);
};

#endif // MAP_H
