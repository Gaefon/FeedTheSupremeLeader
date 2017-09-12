#include <models/Texture.h>
#include <commands/SingleCommandBuffer.h>
#include <vulkan/vulkan.h>

#include <string.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	Texture::Texture(Device *dev, Bitmap *bmp) : image(dev), buffer(dev), image_view(dev)
	{
		bitmap = bmp;
		device = dev;
		
		buffer.createBuffer(bitmap->getWidth() * bitmap->getHeight() * sizeof(uint32_t));		
		buffer.allocBuffer();
		buffer.bindToDevice();
		
		// invert pixels because texture begin at the bottom
		data = new unsigned int[bitmap->getWidth() * bitmap->getHeight()];
		for (unsigned int i = 0; i < bitmap->getHeight(); i++)
		{
			void *line = &(bitmap->getPixels()[(bitmap->getHeight() - i - 1) * bitmap->getWidth()]);
			memcpy(&data[i * bitmap->getWidth()], line, bitmap->getWidth() * sizeof(uint32_t));
		}
		
		buffer.addData(data, bitmap->getWidth() * bitmap->getHeight() * sizeof(uint32_t));
		
		image.createImage(bitmap->getWidth(), bitmap->getHeight(), VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
		
		image.bindToBuffer(&buffer);
		
		image_view.createImageView(&image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
	}
	
	void Texture::setSampler(Sampler *smplr)
	{
		m_sampler = smplr;
	}
	
	Sampler *Texture::getSampler()
	{
		return m_sampler;
	}
	
	Texture::~Texture()
	{
		image.destroyImage();
		
		delete data;
	}
	
	Bitmap *Texture::getBitmap()
	{
		return bitmap;
	}
	
	Image *Texture::getImage()
	{
		return &image;
	}
	
	ImageView *Texture::getImageView()
	{
		return &image_view;
	}
	
	void Texture::prepareTexture(CommandPool *pool)
	{
		SingleCommandBuffer cmd(device);
		cmd.createCommandBuffer(pool);
		cmd.begin();
		image.transitionImageLayout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &cmd);
		cmd.end();
		cmd.submit();
		
		SingleCommandBuffer cmd_copy(device);
		cmd_copy.createCommandBuffer(pool);
		cmd_copy.begin();
		image.copyFromBuffer(&buffer, &cmd_copy);
		cmd_copy.end();
		cmd_copy.submit();
		
		SingleCommandBuffer cmd_trans(device);
		cmd_trans.createCommandBuffer(pool);
		cmd_trans.begin();
		image.transitionImageLayout(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, &cmd_trans);
		cmd_trans.end();
		cmd_trans.submit();
	}
}

