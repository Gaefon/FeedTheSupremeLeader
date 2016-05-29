#include <uiclass/Button.h>
#include <Constants.hpp>
#include <helper/RectHelper.h>
#include <helper/ColorHelper.h>


using namespace std;

Button::Button(MainWindow *prnt, int pos_x, int pos_y, SDL_Surface *img_button, string text): Widget(prnt)
{
	m_is_over = false;
	m_is_pressed = false;
	m_is_clicked = false;

	m_text_font = TTF_OpenFont("ressources/kremlin.ttf", 20);

	m_dst.x = pos_x;
	m_dst.y = pos_y;
	m_dst.w = img_button->w;
	m_dst.h = img_button->h / 3;
	m_src.x = 0;
	m_src.y = 0;
	m_src.w = img_button->w;
	m_src.h = img_button->h / 3;
	m_button_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), img_button);

	setText(text);
}

Button::~Button()
{
	TTF_CloseFont(m_text_font);
	SDL_DestroyTexture(m_button_text_normal);
	SDL_DestroyTexture(m_button_text_over);
	SDL_DestroyTexture(m_button_texture);
}

int Button::getWidth()
{
	return m_dst.w;
}

int Button::getHeight()
{
	return m_dst.h;
}

void Button::setPosition(int x, int y)
{
	m_dst.x = x;
	m_dst.y = y;

	m_dst_text.x = m_dst.x + (m_dst.w / 2) - (m_src_text.w / 2);
	m_dst_text.y = m_dst.y + (m_dst.h / 2) - (m_src_text.h / 2);
}

void Button::setText(string text)
{
	SDL_Surface *srfce_normal;
	SDL_Surface *srfce_over;
	SDL_Color color_normal;
	SDL_Color color_over;

	ColorHelper::parseColor(&color_normal, COLOR_YELLOW);
	ColorHelper::parseColor(&color_over, COLOR_LIGHT_YELLOW);

	m_btn_str = text;
	srfce_normal = TTF_RenderText_Blended(m_text_font, m_btn_str.c_str(), color_normal);
	srfce_over = TTF_RenderText_Blended(m_text_font, m_btn_str.c_str(), color_over);

	m_src_text.x = 0;
	m_src_text.y = 0;
	m_src_text.w = srfce_normal->w;
	m_src_text.h = srfce_normal->h;

	m_dst_text.x = m_dst.x + (m_dst.w / 2) - (m_src_text.w / 2);
	m_dst_text.y = m_dst.y + (m_dst.h / 2) - (m_src_text.h / 2);
	m_dst_text.w = srfce_normal->w;
	m_dst_text.h = srfce_normal->h;


	m_button_text_normal = SDL_CreateTextureFromSurface(getParent()->getRenderer(), srfce_normal);
	m_button_text_over = SDL_CreateTextureFromSurface(getParent()->getRenderer(), srfce_over);

	SDL_FreeSurface(srfce_normal);
	SDL_FreeSurface(srfce_over);
}

bool Button::isClicked()
{
	if (m_is_clicked)
	{
		m_is_clicked = false;
		return true;
	}
	return false;
}

bool Button::onSdlEventReceived(SDL_Event event)
{
	bool rtn_val = false;
	switch (event.type)
	{
		case SDL_MOUSEMOTION:
			if (RectHelper::isInRect(&m_dst, event.motion.x, event.motion.y))
				m_is_over = true;
			else
			{
				m_is_over = false;
				m_is_pressed = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (RectHelper::isInRect(&m_dst, event.button.x, event.button.y))
			{
				m_is_pressed = true;
				rtn_val = true;
			}
			else
				m_is_over = false;
			break;
		case SDL_MOUSEBUTTONUP:
			if (m_is_pressed && RectHelper::isInRect(&m_dst, event.button.x, event.button.y))
			{
				m_is_clicked = true;
				rtn_val = true;
			}
			m_is_pressed = false;
			break;
	}
	return rtn_val;
}

void Button::draw()
{
	if (m_is_pressed)
		m_src.y = m_src.h * 2;
	else if (m_is_over)
		m_src.y = m_src.h;
	else
		m_src.y = 0;

	SDL_RenderCopy(getParent()->getRenderer(), m_button_texture, &m_src, &m_dst);

	if (!m_is_pressed)
		SDL_RenderCopy(getParent()->getRenderer(), m_button_text_normal, &m_src_text, &m_dst_text);
	else
		SDL_RenderCopy(getParent()->getRenderer(), m_button_text_over, &m_src_text, &m_dst_text);
}