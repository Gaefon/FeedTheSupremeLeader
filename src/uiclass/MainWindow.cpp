#include <SDL.h>
#include <uiclass/MainWindow.hpp>
#include <Constants.hpp>


MainWindow::MainWindow()
{
	m_width = WINDOW_DEFAULT_WIDTH;
	m_height = WINDOW_DEFAULT_HEIGHT;
	m_fullscreen = false;
	m_request_close = false;
}

void MainWindow::setSize(unsigned int w, unsigned int h)
{
	m_width = w;
	m_height = h;
	SDL_SetWindowSize(m_window, m_width, m_height);
}

unsigned int MainWindow::getWidth()
{
	return m_width;
}

unsigned int MainWindow::getHeight()
{
	return m_height;
}

bool MainWindow::getFullscreen()
{
	return m_fullscreen;
}

void MainWindow::setFullscreen(bool val)
{
	m_fullscreen = val;
	if (m_fullscreen)
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(m_window, 0);
}

void MainWindow::displayWindow()
{
	m_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, 0);
}

bool MainWindow::hasCloseRequest()
{
	return m_request_close;
}

MainWindow::~MainWindow()
{
	SDL_DestroyWindow(m_window);
}
