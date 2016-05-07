#include "MainWindow.hpp"

MainWindow::MainWindow()
{
	//ctor
}

unsigned int getWidth()
{
	return m_width;
}

void setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int getHeight()
{
	return m_height;
}

void setHeight(unsigned int val)
{
	m_height = val;
}

bool getFullscreen()
{
	return m_fullscreen;
}

void setFullscreen(bool val)
{
	m_fullscreen = val;
}

MainWindow::~MainWindow()
{
	//dtor
}
