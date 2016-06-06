#include <uiclass/Slider.h>
#include <Constants.hpp>
#include <helper/RectHelper.h>
#include <helper/ColorHelper.h>

using namespace std;

Slider::Slider(MainWindow *prnt, int pos_x, int pos_y, SDL_Surface *img_slider) : Widget(prnt)
{
    m_is_over = false;
    m_is_sliding = false;
    m_value = 50;

    m_dst.x = pos_x;
	m_dst.y = pos_y;
	m_dst.w = img_slider->w;
	m_dst.h = img_slider->h / 3;
	m_src.x = 0;
	m_src.y = 0;
	m_src.w = img_slider->w;
	m_src.h = img_slider->h / 3;
	m_slider_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), img_slider);
}

Slider::~Slider(){};

int Slider::getWidth()
{
	return m_dst.w;
}

int Slider::getHeight()
{
	return m_dst.h;
}

void Slider::setPosition(int x, int y)
{
	m_dst.x = x;
	m_dst.y = y;
}

bool Slider::onSdlEventReceived(SDL_Event event)
{
	int rtn_val = m_value;
	switch (event.type)
	{
	    int x, y;
	    SDL_GetMouseState(&x, &y);
		case SDL_MOUSEMOTION:
			if (RectHelper::isInRect(&m_dst, event.motion.x, event.motion.y))
				m_is_over = true;
			else
			{
				m_is_over = false;
				m_is_sliding = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (RectHelper::isInRect(&m_dst, event.button.x, event.button.y))
			{
				m_is_sliding = true;
			}
			else
				m_is_over = false;
			break;
		case SDL_MOUSEBUTTONUP:
			if (m_is_sliding && RectHelper::isInRect(&m_dst, event.button.x, event.button.y))
			{
				m_is_sliding = false;
				rtn_val = rtn_val - (m_dst.x - x);
			}
			m_is_sliding = false;
			break;
	}
	return rtn_val;
}

void Slider::draw()
{
	if (m_is_sliding)
		m_src.y = m_src.h * 2;
	else if (m_is_over)
		m_src.y = m_src.h;
	else
		m_src.y = 0;

	SDL_RenderCopy(getParent()->getRenderer(), m_slider_texture, &m_src, &m_dst);
/*
	if (m_sli_text_normal != NULL && m_button_text_over != NULL)
	{
		if (!m_is_pressed)
			SDL_RenderCopy(getParent()->getRenderer(), m_button_text_normal, &m_src_text, &m_dst_text);
		else
			SDL_RenderCopy(getParent()->getRenderer(), m_button_text_over, &m_src_text, &m_dst_text);
	}*/
}
