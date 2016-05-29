#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>
#include <utilities/Observer/SdlObserver.h>

class Button: public Widget, public SdlObserver
{
	private:
		SDL_Rect m_dst;
		SDL_Rect m_src;
		SDL_Rect m_dst_text;
		SDL_Rect m_src_text;
		SDL_Texture *m_button_texture;
		SDL_Texture *m_button_text_normal;
		SDL_Texture *m_button_text_over;
		TTF_Font *m_text_font;

		std::string m_btn_str;

		bool m_is_over;
		bool m_is_pressed;
		bool m_is_clicked;

	public:
		Button(MainWindow *prnt, int pos_x, int pos_y, SDL_Surface *img_button, std::string text);
		~Button();
		int getWidth();
		int getHeight();
		void setPosition(int x, int y);
		void setText(std::string text);
		bool isClicked();

		void onSdlEventReceived(SDL_Event event);
		void draw();
};

#endif