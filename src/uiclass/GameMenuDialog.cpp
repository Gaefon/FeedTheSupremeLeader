#include <uiclass/GameMenuDialog.h>

GameMenuDialog::GameMenuDialog(MainWindow *parent, int w, int h): Widget(parent)
{
	m_width = w;
	m_height = h;

	m_is_visible = false;
}

GameMenuDialog::~GameMenuDialog()
{
}

int GameMenuDialog::getWidth()
{
	return m_width;
}

int GameMenuDialog::getHeight()
{
	return m_height;
}

void GameMenuDialog::draw()
{
	if (m_is_visible)
	{}
}

void GameMenuDialog::onSdlEventReceived(SDL_Event event)
{
	if (m_is_visible)
	{}
}