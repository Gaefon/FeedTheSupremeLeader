#ifndef MINIMAP_H
#define MINIMAP_H

#include <uiclass/Widget.h>
#include <model/Map.h>
#include <SDL.h>

class Minimap: public Widget
{
	private:
		Map *m_map;
		SDL_Rect m_map_pos_rect;
		SDL_Rect draw_rect;
		SDL_Color default_color;

	public:
		Minimap(MainWindow *parent, int pos_x, int pos_y, Map *map);
		~Minimap();
		int getWidth();
		int getHeight();
		void draw();
};

#endif