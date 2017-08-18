#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <Device.h>
#include <Image.h>
#include <bitmaps/BMPImage.h>

namespace GEngine
{
	class Texture
	{
		private:
			Image image;
			Bitmap *bitmap;
		public:
			Texture(Device *dev, Bitmap *bmp);
			~Texture();
			Bitmap *getBitmap();
			Image *getImage();
		
	};
}

#endif
