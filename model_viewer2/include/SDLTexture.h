#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <SDL2/SDL.h>
#include "Texture.h"

class SDLTexture: public Texture
{
	private:
		SDL_Surface *m_texture;
		
		void invertPixels();
		
	public:
		SDLTexture();
		SDLTexture(std::string filename);
		~SDLTexture();
		void loadTexture(std::string file_name);
};

#endif
