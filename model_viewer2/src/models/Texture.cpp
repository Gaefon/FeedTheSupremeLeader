#include <models/Texture.h>

#include <vulkan/vulkan.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	Texture::Texture(Device *dev, Bitmap *bmp) : image(dev)
	{
		bitmap = bmp;
		image.createImage(bitmap->getWidth(), bitmap->getHeight(), VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
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
}

