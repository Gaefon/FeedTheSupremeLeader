#include <uiclass/Slider.h>
#include <Constants.hpp>
#include <helper/RectHelper.h>
#include <helper/ColorHelper.h>

using namespace std;

Slider::Slider(MainWindow *prnt, int pos_x, int pos_y, SDL_Surface *img_slider, int custom_width) : Widget(prnt)
{
	m_is_over = false;
	m_is_sliding = false;
	m_slide_finished = false;
	m_value = 50;

	m_dst.x = pos_x;
	m_dst.y = pos_y;
	if(custom_width == 0)
		m_dst.w = img_slider->w;
	else
		m_dst.w = custom_width;
	m_dst.h = img_slider->h / 3;
	m_src.x = 0;
	m_src.w = img_slider->w;
	m_src.h = img_slider->h / 3;
	m_slider_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), img_slider);
}

Slider::~Slider()
{}

int Slider::getWidth()
{
	return m_dst.w;
}

int Slider::getHeight()
{
	return m_dst.h;
}

int Slider::getValue()
{
	return m_value;
}

void Slider::setValue(int value)
{
	m_value = value;
}

bool Slider::isSliding()
{
	return m_is_sliding;
}

bool Slider::slideFinished()
{
	if (m_slide_finished)
	{
		m_slide_finished = false;
		return true;
	}
	return false;
}

void Slider::setPosition(int x, int y)
{
	m_dst.x = x;
	m_dst.y = y;
}

bool Slider::onSdlEventReceived(SDL_Event event)
{
	bool rtn_val = false;
	bool in_rect;
	switch (event.type)
	{
		case SDL_MOUSEMOTION:
			in_rect = RectHelper::isInRect(&m_dst, event.motion.x, event.motion.y);
			if (!in_rect && m_is_sliding)
				m_slide_finished = true;
			if (in_rect && m_is_sliding)
				m_value = (event.motion.x - m_dst.x) * 100 / m_dst.w;
			else
				m_is_sliding = false;
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
			if(m_is_sliding)
				m_value = (event.motion.x - m_dst.x) * 100 / m_dst.w;
			m_is_sliding = false;
			if (RectHelper::isInRect(&m_dst, event.button.x, event.button.y))
				m_slide_finished = true;
			break;
	}
	return rtn_val;
}

void Slider::draw()
{
	if (isVisible())
	{
		drawBar();
		drawSquare();
	}
}

void Slider::drawBar()
{
	SDL_Rect bar_src;
	SDL_Rect bar_part_dst = m_dst;
	SDL_Rect bar_part_src = m_src;

	bar_src.x = m_src.x;
	bar_src.y = 0;
	bar_src.w = m_src.w;
	bar_src.h = m_src.h;
	bar_part_dst.w = m_dst.w * m_value / 100;
	bar_part_src.y = m_src.h;
	SDL_RenderCopy(getParent()->getRenderer(), m_slider_texture, &bar_src, &m_dst);
	SDL_RenderCopy(getParent()->getRenderer(), m_slider_texture, &bar_part_src, &bar_part_dst);
}

void Slider::drawSquare()
{
	SDL_Rect square_dst = m_dst;
	SDL_Rect square_src = m_src;
	square_dst.w = square_dst.h = m_src.h;
	square_dst.x = m_dst.x + m_dst.w * m_value / 100 - square_dst.w / 2;
	square_src.x = 0;
	square_src.w = square_src.h = m_src.h;
	square_src.y = square_src.h * 2;
	SDL_RenderCopy(getParent()->getRenderer(), m_slider_texture, &square_src, &square_dst);
}


