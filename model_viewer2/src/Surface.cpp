#include <Surface.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

namespace GEngine
{
	Surface::Surface(Engine *instance, Window *window)
	{
		init(instance, window);
	}
	
	Surface::~Surface()
	{
	}
	
	bool Surface::init(Engine *instance, Window *window)
	{
		VkResult err = glfwCreateWindowSurface(instance->getVulkanObject(), window->getGLFWObject(), NULL, &surface);
		
		if (err)
		{
			cerr << "Create surface failed" << endl;
			// Window surface creation failed
			return false;
		}
		
		return true;
	}
	
	
	PhysicalDevice *Surface::getSuitableDevice(Engine *instance)
	{
		int graphic;
		int present;
		
		for (PhysicalDevice *dev: instance->getListPhysicalDevices())
		{
			getFirstValidQueueFamily(dev, &graphic, &present);
			if (dev->isSuitable(instance->getExtensions()) && present >= 0 && graphic >= 0 && isDeviceCompatible(dev))
				return dev;
		}
		return nullptr;
	}
	
	void Surface::getFirstValidQueueFamily(PhysicalDevice *physical_device, int *graphic, int *present)
	{
		unsigned int queue_family_count = 0;
		
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device->getVulkanObject(), &queue_family_count, nullptr);
		
		vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device->getVulkanObject(), &queue_family_count, queue_families.data());
		
		unsigned int i = 0;
		*graphic = -1;
		*present = -1;
		
		for (VkQueueFamilyProperties queue: queue_families)
		{
			if (queue.queueCount > 0 && queue.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				*graphic = i;
			}
			
			VkBool32 support_present = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physical_device->getVulkanObject(), i, surface, &support_present);
			
			if (queue.queueCount > 0 && support_present)
				*present = i;
			
			if (*graphic >= 0 && *present >= 0)
			{
				physical_device->setPresentIndex(*present);
				physical_device->setGraphicIndex(*graphic);
				break;
			}
			i++;
		}
	}
	
	bool Surface::isDeviceCompatible(PhysicalDevice *dev)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev->getVulkanObject(), surface, &capabilities);
		
		unsigned int format_count;
		vkGetPhysicalDeviceSurfaceFormatsKHR(dev->getVulkanObject(), surface, &format_count, nullptr);
		
		if (format_count != 0)
		{
			formats.resize(format_count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(dev->getVulkanObject(), surface, &format_count, formats.data());
		}
		
		unsigned int present_mode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(dev->getVulkanObject(), surface, &present_mode_count, nullptr);

		if (present_mode_count != 0)
		{
			present_modes.resize(present_mode_count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(dev->getVulkanObject(), surface, &present_mode_count, present_modes.data());
		}
		
		return !formats.empty() && !present_modes.empty();
	}
	
	VkSurfaceFormatKHR Surface::chooseSwapSurfaceFormat()
	{
		if (formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
			return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};

		for (const VkSurfaceFormatKHR &format : formats)
		{
			if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return format;
		}

		return formats[0];
	}
	
	VkPresentModeKHR Surface::chooseSwapPresentMode()
	{
		VkPresentModeKHR best_mode = VK_PRESENT_MODE_FIFO_KHR;
	
		for (const VkPresentModeKHR &mode : present_modes)
		{
			if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
				return mode;
			else if (mode == VK_PRESENT_MODE_IMMEDIATE_KHR)
				best_mode = mode;
		}
		return best_mode;
	}
	
	VkExtent2D Surface::chooseSwapExtent(Window *window)
	{
		if (capabilities.currentExtent.width != numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		
		VkExtent2D actual_extent = {window->getWidth(), window->getHeight()};

		actual_extent.width = max(capabilities.minImageExtent.width, min(capabilities.maxImageExtent.width, actual_extent.width));
		actual_extent.height = max(capabilities.minImageExtent.height, min(capabilities.maxImageExtent.height, actual_extent.height));

		return actual_extent;
	}
	
	VkSurfaceCapabilitiesKHR Surface::getCapabilities()
	{
		return capabilities;
	}
	
	
	VkSurfaceKHR Surface::getVulkanObject()
	{
		return surface;
	}
	
}
