#include <Image.h>

#include <iostream>

using namespace std;

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
	
	bool Image::createImage(uint32_t width, uint32_t height, VkFormat format)
	{
		// create the image
		VkImageCreateInfo image_info = {};
		image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_info.imageType = VK_IMAGE_TYPE_2D;
		image_info.extent.width = width;
		image_info.extent.height = height;
		image_info.extent.depth = 1;
		image_info.mipLevels = 1;
		image_info.arrayLayers = 1;
		image_info.format = format;
		image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
		image_info.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
		image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		image_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateImage(device->getVulkanObject(), &image_info, nullptr, &m_image) != VK_SUCCESS)
		{
			cerr << "failed to create image!" << endl;
			return false;
		}
	
		return true;
	}
	
	VkImage *Image::getVulkanObject()
	{
		return &m_image;
	}
}
