#include <SDLTexture.h>

#include <iostream>

using namespace std;

SDLTexture::SDLTexture()
{
}

SDLTexture::SDLTexture(string file_name)
{
	loadTexture(file_name);
}

SDLTexture::~SDLTexture()
{
	SDL_FreeSurface(m_texture);
}

void SDLTexture::loadTexture(std::string file_name)
{
	m_texture = SDL_LoadBMP(file_name.c_str());
	if (m_texture == NULL)
		cerr << "SDL TEXTURE :: can't load file : " << file_name << endl;
	invertPixels();
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	GLenum internal_format = 0;
	GLenum format = 0;

	if (m_texture->format->BytesPerPixel == 3)
	{
		internal_format = GL_RGB;
		if (m_texture->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;
	}
	else if (m_texture->format->BytesPerPixel == 4)
	{
		internal_format = GL_RGBA;
		if (m_texture->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}
	else
		cerr << "TESTURE :: Wrong color format" << endl;

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_texture->w, m_texture->h, 0, format, GL_UNSIGNED_BYTE, m_texture->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void SDLTexture::invertPixels()
{
	int p_size = m_texture->format->BytesPerPixel;
	int pos_src;
	int pos_dst;
	char tmp;

	for (int i = 0; i < m_texture->h / 2; ++i)
	{
		for (int j = 0; j < m_texture->w * p_size; ++j)
		{
			pos_src = (i * m_texture->w * p_size) + j;
			pos_dst = ((m_texture->h - i - 1) * m_texture->w * p_size) + j;
			tmp = ((char *) m_texture->pixels)[pos_dst];
			((char *) m_texture->pixels)[pos_dst] = ((char *) m_texture->pixels)[pos_src];
			((char *) m_texture->pixels)[pos_src] = tmp;
		}
	}

	SDL_SaveBMP(m_texture, "LOLOLOLOL.bmp");
}

