#include <uiclass/Commissar.h>
#include <utilities/RessourceManager.h>

Commissar::Commissar(MainWindow *prnt, int pos_x, int pos_y): Widget(prnt)
{
	SDL_Surface *img_com = RessourceManager::getInstance()->getSurface(RessourceManager::Commissar);
	rect_img.x = pos_x;
	rect_img.y = pos_y;
	rect_img.w = img_com->w;
	rect_img.h = img_com->h;
	m_commissar_photo = SDL_CreateTextureFromSurface(getParent()->getRenderer(), img_com);
}

Commissar::~Commissar()
{
	SDL_DestroyTexture(m_commissar_photo);
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
		SDL_RenderCopy(getParent()->getRenderer(), m_commissar_photo, NULL, &rect_img);
	}
}
