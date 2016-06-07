#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>
#include <utilities/RessourceManager.h>

class Label: public Widget
{
	private:
		SDL_Texture *m_texture_text;
		SDL_Rect m_src;
		SDL_Rect m_dst;

		TTF_Font *m_text_font;
		std::string m_str;

	public:
		Label(MainWindow *prnt, int x, int y, std::string text);
		~Label();

		int getWidth();
		int getHeight();
		void setPosition(int x, int y);
		void setFont(RessourceManager::FontEntities font);
		void setText(std::string text);
		void draw();
};

#endif