#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <Device.h>
#include <Image.h>
#include <ImageView.h>
#include <bitmaps/BMPImage.h>
#include <buffers/StagingBuffer.h>
#include <commands/CommandPool.h>
#include <Sampler.h>

namespace GEngine
{
	class Texture
	{
		private:
			Device *device;
			Image image;
			Bitmap *bitmap;
			StagingBuffer buffer;
			ImageView image_view;
			
			Sampler *m_sampler;
			
			unsigned int *data;
			
			
		public:
			Texture(Device *dev, Bitmap *bmp);
			~Texture();
			
			void setSampler(Sampler *smplr);
			Sampler *getSampler();
			
			Bitmap *getBitmap();
			Image *getImage();
			ImageView *getImageView();
			
			void prepareTexture(CommandPool *pool);
		
	};
}

#endif
