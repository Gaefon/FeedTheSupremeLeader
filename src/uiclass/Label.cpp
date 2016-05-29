#include <Constants.hpp>
#include <uiclass/Label.h>
#include <helper/ColorHelper.h>

Label::Label(MainWindow *prnt, int x, int y, std::string text): Widget(prnt)
{
	m_text_font = TTF_OpenFont("ressources/kremlin.ttf", 20);

	m_src.x = 0;
	m_src.y = 0;
	setPosition(x, y);
	setText(text);
}

Label::~Label()
{
	TTF_CloseFont(m_text_font);
	SDL_DestroyTexture(m_texture_text);
}

int Label::getWidth()
{
	return m_dst.w;
}

int Label::getHeight()
{
	return m_dst.h;
}

void Label::setPosition(int x, int y)
{
	m_dst.x = x;
	m_dst.y = y;
}

void Label::setFontSize(int size)
{
	TTF_CloseFont(m_text_font);
	m_text_font = TTF_OpenFont("ressources/kremlin.ttf", size);
	setText(m_str);
}

void Label::setText(std::string text)
{
	SDL_Surface *srfce;
	SDL_Color color_text;

	ColorHelper::parseColor(&color_text, COLOR_YELLOW);
	m_str = text;

	srfce = TTF_RenderText_Blended(m_text_font, m_str.c_str(), color_text);

	m_src.w = srfce->w;
	m_src.h = srfce->h;
	m_dst.w = srfce->w;
	m_dst.h = srfce->h;

	m_texture_text = SDL_CreateTextureFromSurface(getParent()->getRenderer(), srfce);

	SDL_FreeSurface(srfce);
}

void Label::draw()
{
	SDL_RenderCopy(getParent()->getRenderer(), m_texture_text, &m_src, &m_dst);
}