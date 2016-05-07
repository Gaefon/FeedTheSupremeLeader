#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


class MainWindow
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_fullscreen;
		bool m_request_close;

		SDL_Window *m_window;
	public:
		MainWindow();
		~MainWindow();
		void setSize(unsigned int w, unsigned int h);
		unsigned int getWidth();
		unsigned int getHeight();
		bool getFullscreen();
		void setFullscreen(bool val);
		bool hasCloseRequest();
		void displayWindow();
};

#endif // MAINWINDOW_HPP
