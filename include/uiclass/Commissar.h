#ifndef COMMISSAR_H
#define COMMISSAR_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>

class Commissar: public Widget
{
	private:
		SDL_Texture *m_commissar_photo;
		SDL_Rect rect_img;
	public:
		Commissar(MainWindow *prnt, int pos_x, int pos_y);
		~Commissar();
		int getWidth();
		int getHeight();
		void draw();
};

#endif