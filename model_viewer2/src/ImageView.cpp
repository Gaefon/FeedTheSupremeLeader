#include <ImageView.h>
#include <iostream>
using namespace std;

namespace GEngine
{
	ImageView::ImageView(Device *dev)
	{
		device = dev;
		image_view = VK_NULL_HANDLE;
	}

    ImageView::ImageView(Device *dev, Image *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat)
    {
	    device = dev;
	    image_view = VK_NULL_HANDLE;
        createImageViewKHR(vkImage, vkSurfaceFormat);
    }
    
	ImageView::ImageView(Device *dev, Image *vkImage, VkFormat format, VkImageAspectFlags aspect_flags)
	{
		device = dev;
		image_view = VK_NULL_HANDLE;
		createImageView(vkImage, format, aspect_flags);
	}

	ImageView::~ImageView()
	{
		if(image_view != VK_NULL_HANDLE)
			vkDestroyImageView(device->getVulkanObject(), image_view, nullptr);
	}
    
    // TODO : Deprecate this method.
    // replace with createImageView(Device *, Image *, VkFormat, VkImageAspectFlags)
    void ImageView::createImageViewKHR(Image *image, VkSurfaceFormatKHR *vkSurfaceFormat)
    {
		image_view = VK_NULL_HANDLE;
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = *image->getVulkanObject();
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = vkSurfaceFormat->format;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.pNext = nullptr;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(device->getVulkanObject(), &createInfo, nullptr, &image_view) != VK_SUCCESS)
		{
			image_view = VK_NULL_HANDLE;
			cerr << "failed to create image view!" << endl;
		}
    }
    
    void ImageView::createImageView(Image *image, VkFormat format, VkImageAspectFlags aspect_flags)
    {
		VkImageViewCreateInfo view_info = {};
		view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		view_info.image = *image->getVulkanObject();
		view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		view_info.format = format;
		view_info.subresourceRange.aspectMask = aspect_flags;
		view_info.subresourceRange.baseMipLevel = 0;
		view_info.subresourceRange.levelCount = 1;
		view_info.subresourceRange.baseArrayLayer = 0;
		view_info.subresourceRange.layerCount = 1;
		
		if (vkCreateImageView(device->getVulkanObject(), &view_info, nullptr, &image_view) != VK_SUCCESS)
		{
			image_view = VK_NULL_HANDLE;
			cerr << "failed to create texture image view!" << endl;
		}
    }

    VkImageView ImageView::getVulkanObject()
    {
        return image_view;
    }
}
