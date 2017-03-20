#include <ImageView.h>
#include <iostream>
using namespace std;

namespace GEngine
{
    ImageView::ImageView(VkImage *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat, Device *device)
    {
        image_view = VK_NULL_HANDLE;
        VkImageViewCreateInfo createInfo = {};
        this->device = device;
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = *vkImage;
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

    ImageView::~ImageView()
    {
        if(image_view != VK_NULL_HANDLE)
        {
            vkDestroyImageView(device->getVulkanObject(), image_view, nullptr);
        }
    }

    VkImageView ImageView::getVulkanObject()
    {
        return image_view;
    }
}
