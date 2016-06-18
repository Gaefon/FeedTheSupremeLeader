#ifndef COMMISSAR_H
#define COMMISSAR_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>

class Commissar: public Widget
{
	private:
		SDL_Texture *m_commissar_photo;
		SDL_Texture *m_text_texture;
		SDL_Rect rect_img;
		SDL_Rect rect_text;

		unsigned int m_duration;
		std::string m_current_text;

		TTF_Font *m_text_font;

	public:
		Commissar(MainWindow *prnt, int pos_x, int pos_y);
		~Commissar();
		void displayText(std::string text, unsigned int ms = 2000);
		int getWidth();
		int getHeight();
		void draw();
};

#endif