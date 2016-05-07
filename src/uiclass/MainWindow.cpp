#include <SDL.h>
#include <uiclass/MainWindow.hpp>


MainWindow::MainWindow()
{
	m_width = 640;
	m_height = 480;
	m_fullscreen = false;
}

unsigned int MainWindow::getWidth()
{
	return m_width;
}

void MainWindow::setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int MainWindow::getHeight()
{
	return m_height;
}

void MainWindow::setHeight(unsigned int val)
{
	m_height = val;
}

bool MainWindow::getFullscreen()
{
	return m_fullscreen;
}

void MainWindow::setFullscreen(bool val)
{
	m_fullscreen = val;
}

void MainWindow::displayWindow()
{
	m_window = SDL_CreateWindow("lol", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, 0);
}

MainWindow::~MainWindow()
{
	SDL_DestroyWindow(m_window);
}
