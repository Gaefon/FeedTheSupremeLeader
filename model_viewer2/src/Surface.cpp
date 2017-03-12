#include <Surface.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

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
			if (dev->isSuitable() && present >= 0 && graphic >= 0)
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
		
		int i = 0;
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
	
	VkSurfaceKHR Surface::getVulkanObject()
	{
		return surface;
	}
	
}
