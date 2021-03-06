#include <uiclass/Commissar.h>
#include <utilities/RessourceManager.h>
#include <helper/ColorHelper.h>
#include <Constants.hpp>
#include <unistd.h>

using namespace std;

Commissar::Commissar(MainWindow *prnt, int pos_x, int pos_y): Widget(prnt)
{
	SDL_Surface *img_com = RessourceManager::getInstance()->getSurface(RessourceManager::Commissar);
	rect_img.x = pos_x;
	rect_img.y = pos_y;
	rect_img.w = img_com->w;
	rect_img.h = img_com->h;
	m_commissar_photo = SDL_CreateTextureFromSurface(getParent()->getRenderer(), img_com);
	// m_displayed_char = 1;
	m_text_font = RessourceManager::getInstance()->getFont(RessourceManager::LatoFont20);

	hide();
}

Commissar::~Commissar()
{
	SDL_DestroyTexture(m_commissar_photo);
}

void Commissar::displayText(string text, unsigned int ms)
{
	SDL_Surface *srfce_text;
	// SDL_Surface *srfce_text_displayed_char;
	SDL_Color color_text;
	// SDL_Color color_background;

	m_duration = ms;
	m_current_text = text;
	string tmp_chars;
	// int tmp_fullfilled = 0;

	// for (int i = 0; i < static_cast<int>(text.length()); i++)	{

		// 	m_displayed_char++;
		// if (i % 1500 == 0) {
			// cout << "ok" << endl;
 		// 	tmp_chars = tmp_chars + text.at(i);
			ColorHelper::parseColor(&color_text, COLOR_YELLOW);

		 	srfce_text = TTF_RenderText_Blended(m_text_font, m_current_text.c_str(), color_text);
			// 	srfce_text = TTF_RenderText_Blended(m_text_font, tmp_chars.c_str(), color_text);
			m_text_texture = SDL_CreateTextureFromSurface(getParent()->getRenderer(), srfce_text);

		 	rect_text.x = rect_img.w + 12;
		 	rect_text.y = 0;
		 	rect_text.w = srfce_text->w;
		 	rect_text.h = srfce_text->h;
		 	show();
			// sleep(1);
			// tmp_fullfilled++;
		// }
	// }

	SDL_FreeSurface(srfce_text);
}

int Commissar::getWidth()
{
	return rect_img.w;
}

int Commissar::getHeight()
{
	return rect_img.h;
}

void Commissar::draw()
{
	if (isVisible())
	{
		if (m_duration <= 0)
			hide();
		m_duration -= FRAME_PAUSE_DURATION;
		SDL_RenderCopy(getParent()->getRenderer(), m_commissar_photo, NULL, &rect_img);
		SDL_SetRenderDrawColor(getParent()->getRenderer(), 50, 50, 50, 255);
		SDL_RenderFillRect(getParent()->getRenderer(), &rect_text);
		SDL_RenderCopy(getParent()->getRenderer(), m_text_texture, NULL, &rect_text);
	}
}
