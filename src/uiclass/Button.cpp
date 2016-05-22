#include <uiclass/Button.h>
#include <helper/RectHelper.h>

using namespace std;

Button::Button(MainWindow *prnt, int pos_x, int pos_y, string file_name)
{
	m_parent = prnt;

	SDL_Surface *img_button = SDL_LoadBMP(file_name.c_str());
	dst.x = pos_x;
	dst.y = pos_y;
	dst.w = img_button->w;
	dst.h = img_button->h / 3;
	src.x = 0;
	src.y = 0;
	src.w = img_button->w;
	src.h = img_button->h / 3;
	m_button_tex = SDL_CreateTextureFromSurface(m_parent->getRenderer(), img_button);
	SDL_FreeSurface(img_button);
}

Button::~Button()
{
	SDL_DestroyTexture(m_button_tex);
}

void Button::onSdlEventReceived(SDL_Event event)
{
	(void) event;
	switch (event.type)
	{
		case SDL_MOUSEMOTION:
			if (RectHelper::isInRect(&dst, event.motion.x, event.motion.y))
				src.y = src.h;
			else
				src.y = 0;
			break;
	}
}

void Button::draw()
{
	SDL_RenderCopy(m_parent->getRenderer(), m_button_tex, &src, &dst);
}