#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>


class Texture
{
	protected:
		GLuint m_id;
	public:
		virtual void loadTexture(std::string file_name) = 0;
		GLuint getId();
};

#endif
