#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <utilities/Observer/SdlObserver.h>

class MainWindow: public SdlObserver
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_fullscreen;
		bool m_request_close;


		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		SDL_Surface *m_screen;
	public:
		MainWindow();
		~MainWindow();
		void setSize(unsigned int w, unsigned int h);
		unsigned int getWidth();
		unsigned int getHeight();
		SDL_Renderer *getRenderer();
		SDL_Surface *getSurface();
		bool getFullscreen();
		void setFullscreen(bool val);
		bool hasCloseRequest();
		void displayWindow();
		void clear();
		void setBackground(SDL_Texture *back);
		void update();
		void onSdlEventReceived(SDL_Event event);
};

#endif // MAINWINDOW_HPP
