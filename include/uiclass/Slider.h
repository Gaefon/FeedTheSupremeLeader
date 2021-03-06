#ifndef SLIDER_H
#define SLIDER_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <uiclass/MainWindow.hpp>
#include <uiclass/Widget.h>
#include <utilities/Observer/SdlObserver.h>

class Slider : public Widget, public SdlObserver
{
    private:
        SDL_Rect m_dst;
		SDL_Rect m_src;
		SDL_Texture *m_slider_texture;
        bool m_is_over;
        bool m_is_sliding;
        bool m_slide_finished;
        int m_value;
        void drawBar();
        void drawSquare();

    public:
        Slider(MainWindow *prnt, int pos_x, int pos_y, SDL_Surface *img_slider, int custom_width = 0);
        ~Slider();
        int getWidth();
		int getHeight();
		int getValue();
        void setValue(int value);
		void setPosition(int x, int y);
		bool isSliding();
        bool slideFinished();

		bool onSdlEventReceived(SDL_Event event);
		void draw();

};
#endif // SLIDER_H
