#include <iostream>
#include <SDL.h>
#include <uiclass/MainWindow.hpp>
#include <Constants.hpp>

using namespace std;

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
	if (m_fullscreen)
	{
		int w, h;
		SDL_GetWindowSize(m_window, &w, &h);
		return w;
	}
	return m_width;
}

unsigned int MainWindow::getHeight()
{
	if (m_fullscreen)
	{
		int w, h;
		SDL_GetWindowSize(m_window, &w, &h);
		return h;
	}
	return m_height;
}

SDL_Renderer *MainWindow::getRenderer()
{
	return m_renderer;
}

SDL_Surface *MainWindow::getSurface()
{
	return m_screen;
}

bool MainWindow::getFullscreen()
{
	return m_fullscreen;
}

void MainWindow::setFullscreen(bool val)
{
	m_fullscreen = val;
	if (m_fullscreen)
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(m_window, 0);
}

void MainWindow::displayWindow()
{
	m_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	m_screen = SDL_GetWindowSurface(m_window);
}

bool MainWindow::hasCloseRequest()
{
	return m_request_close;
}

void MainWindow::clear()
{
	SDL_RenderClear(m_renderer);
}

void MainWindow::update()
{
	SDL_UpdateWindowSurface(m_window);
	SDL_RenderPresent(m_renderer);
}

void MainWindow::onSdlEventReceived(SDL_Event event)
{
	(void) event;
	if (event.type == SDL_WINDOWEVENT)
	{
		switch (event.window.event)
		{
			case SDL_WINDOWEVENT_CLOSE:
				m_request_close = true;
				break;
		}
	}
}

MainWindow::~MainWindow()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}
