#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


class MainWindow
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_fullscreen;
	public:
		MainWindow();
		~MainWindow();
		unsigned int getWidth();
		void setWidth(unsigned int val);
		unsigned int getHeight();
		void setHeight(unsigned int val);
		bool getFullscreen();
		void setFullscreen(bool val);
		void displayWindow();
};

#endif // MAINWINDOW_HPP
