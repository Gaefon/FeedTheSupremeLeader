#include <SwapChain.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	SwapChain::SwapChain(Device *dev)
	{
	    logical_device = dev;
	    swap_chain = VK_NULL_HANDLE;
	}

	SwapChain::~SwapChain()
	{
		vkDestroySwapchainKHR(logical_device->getVulkanObject(), swap_chain, nullptr);
		for(vector<ImageView *>::iterator it = image_views.begin(); it != image_views.end(); it++)
        {
            delete *it;
        }
        image_views.clear();
	}

	// TODO stocker les vkImages dans les objets Image associés
	vector<VkImage> SwapChain::getImages()
	{
		unsigned int image_count;

		vkGetSwapchainImagesKHR(logical_device->getVulkanObject(), swap_chain, &image_count, nullptr);
		vector<VkImage> swap_chain_images(image_count);
		vkGetSwapchainImagesKHR(logical_device->getVulkanObject(), swap_chain, &image_count, swap_chain_images.data());

		return swap_chain_images;
	}
	
	bool SwapChain::createSwapChain(Surface *surface, Window *window, PhysicalDevice *phys_dev)
	{
		surface_format = surface->chooseSwapSurfaceFormat();
		VkPresentModeKHR present_mode = surface->chooseSwapPresentMode();
		extent = surface->chooseSwapExtent(window);

		uint32_t image_count = surface->getCapabilities().minImageCount + 1;
		if (surface->getCapabilities().maxImageCount > 0 && image_count > surface->getCapabilities().maxImageCount)
		{
			image_count = surface->getCapabilities().maxImageCount;
		}

		VkSwapchainCreateInfoKHR create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = surface->getVulkanObject();
		create_info.minImageCount = image_count;
		create_info.imageFormat = surface_format.format;
		create_info.imageColorSpace = surface_format.colorSpace;
		create_info.imageExtent = extent;
		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		unsigned int queue_family_indices[] = { phys_dev->getGraphicIndex(), phys_dev->getPresentIndex() };
		if (phys_dev->getGraphicIndex() != phys_dev->getPresentIndex())
		{
			create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			create_info.queueFamilyIndexCount = 2;
			create_info.pQueueFamilyIndices = queue_family_indices;
		}
		else
		{
			create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			create_info.queueFamilyIndexCount = 0;
			create_info.pQueueFamilyIndices = nullptr;
		}

		create_info.preTransform = surface->getCapabilities().currentTransform;
		create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		create_info.presentMode = present_mode;
		create_info.clipped = VK_TRUE;

		create_info.oldSwapchain = VK_NULL_HANDLE;
		vector<VkImage> swap_chain_images(image_count);
		if (vkCreateSwapchainKHR(logical_device->getVulkanObject(), &create_info, nullptr, &swap_chain) != VK_SUCCESS)
		{
			swap_chain = VK_NULL_HANDLE;
			cerr << "failed to create swap chain!" << endl;
			return false;
		}
		return true;
	}

	void SwapChain::initImageViews()
	{
        vector<VkImage> sc_images = getImages();
        //image_views.resize(sc_images.size(), nullptr);
        image_views.clear();
	    for (VkImage image : sc_images)
		{
			ImageView *image_view = new ImageView(&image, &surface_format, logical_device);
			image_views.push_back(image_view);
		}
	}

	vector<ImageView *> SwapChain::getImageViews()
	{
		return image_views;
	}
	
	VkSurfaceFormatKHR SwapChain::getSurfaceFormat()
	{
		return surface_format;
	}
	
	VkExtent2D SwapChain::getExtent()
	{
		return extent;
	}
	
	VkSwapchainKHR SwapChain::getVulkanObject()
	{
		return swap_chain;
	}
}
