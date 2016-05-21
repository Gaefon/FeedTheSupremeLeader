#include <uiclass/Button.h>

Button::Button(MainWindow *prnt, int pos_x, int pos_y)
{
	m_parent = prnt;
	m_x = pos_x;
	m_y = pos_y;
}

Button::~Button()
{
}

void Button::onSdlEventReceived(SDL_Event event)
{
	(void) event;
}