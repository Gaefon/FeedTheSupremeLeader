#include <Image.h>

#include <string.h>

namespace GEngine
{
	Image::Image(Device *dev)
	{
		device = dev;
		m_image = VK_NULL_HANDLE;
	}
	
	Image::Image(Device *dev, VkImage image)
	{
		device = dev;
		m_image = image;
		//memcpy(&m_image, &image, sizeof(VkImage));
	}
	
	Image::~Image()
	{
		/*if (m_image != VK_NULL_HANDLE)
		{
			vkDestroyImage(device->getVulkanObject(), m_image, nullptr);
		}*/
	}
	
	bool Image::createImage()
	{
		return true;
	}
	
	VkImage *Image::getVulkanObject()
	{
		return &m_image;
	}
}
