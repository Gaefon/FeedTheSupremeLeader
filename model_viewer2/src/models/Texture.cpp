#include <models/Texture.h>
#include <commands/SingleCommandBuffer.h>
#include <vulkan/vulkan.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	Texture::Texture(Device *dev, Bitmap *bmp) : image(dev), buffer(dev)
	{
		bitmap = bmp;
		device = dev;
		
		buffer.createBuffer(bitmap->getWidth() * bitmap->getHeight() * sizeof(uint32_t));		
		buffer.allocBuffer();
		buffer.bindToDevice();
		buffer.addData(bitmap->getPixels(), bitmap->getWidth() * bitmap->getHeight() * sizeof(uint32_t));
		
		image.createImage(bitmap->getWidth(), bitmap->getHeight(), VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
		
		image.bindToBuffer(&buffer);
	}
	
	Texture::~Texture()
	{
		image.destroyImage();
	}
	
	Bitmap *Texture::getBitmap()
	{
		return bitmap;
	}
	
	Image *Texture::getImage()
	{
		return &image;
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

