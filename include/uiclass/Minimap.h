#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL.h>
#include <uiclass/Widget.h>
#include <utilities/Observer/SdlObserver.h>
#include <model/Map.h>

class Minimap: public Widget, public SdlObserver
{
	private:
		Map *m_map;
		SDL_Rect m_map_pos_rect;
		SDL_Rect m_draw_rect;
		SDL_Color m_default_color;

		bool m_is_clicked;

	public:
		Minimap(MainWindow *parent, int pos_x, int pos_y, Map *map);
		~Minimap();
		int getWidth();
		int getHeight();
		void setPosition(int x, int y);
		bool onSdlEventReceived(SDL_Event event);
		void draw();
};

#endif