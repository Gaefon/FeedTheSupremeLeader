#include <Device.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	Device::Device(Surface surface, PhysicalDevice phys_dev)
	{
		device = VK_NULL_HANDLE;
		if (!init(surface, phys_dev))
			device = VK_NULL_HANDLE;
	}
	
	Device::~Device()
	{
		if (device != VK_NULL_HANDLE)
			vkDestroyDevice(device, nullptr);
	}
	
	bool Device::init(Surface surface, PhysicalDevice phys_dev)
	{
		priority = 1.0f;
		
		/*int present;
		int graphic;
		
		phys_dev.getFirstValidQueueFamily(surface, &present, &graphic);*/

		VkDeviceQueueCreateInfo queue_create_info = {};
		queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.queueFamilyIndex = ;
		queue_create_info.queueCount = 1;
		queue_create_info.pQueuePriorities = &priority;
	
		device_create_infos = {};
		device_create_infos.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_create_infos.pQueueCreateInfos = &queue_create_info;
		device_create_infos.queueCreateInfoCount = 1;
		device_create_infos.pEnabledFeatures = phys_dev.getFeatures();
		
		device_create_infos.enabledExtensionCount = 0;
		device_create_infos.enabledLayerCount = 0;
		
		
		if (vkCreateDevice(phys_dev.getVulkanObject(), &device_create_infos, nullptr, &device) != VK_SUCCESS)
		{
		    cerr << "Failed to create device." << endl;
		    return false;
		}
		
		vkGetDeviceQueue(device, phys_dev.getFirstValidQueueFamily(), 0, &device_queue);
		/*if (vkGetDeviceQueue(device, phys_dev.getFirstValidQueueFamily(), 0, &device_queue) != VK_SUCCESS)
		{
		    cerr << "Failed to create queue." << endl;
		    return false;
		}*/
		
		return true;
	}
}
