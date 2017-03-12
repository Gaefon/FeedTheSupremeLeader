#include <Device.h>

#include <iostream>
#include <set>
#include <vector>

using namespace std;

namespace GEngine
{
	Device::Device(PhysicalDevice *phys_dev)
	{
		device = VK_NULL_HANDLE;
		if (!init(phys_dev))
			device = VK_NULL_HANDLE;
	}
	
	Device::~Device()
	{
		if (device != VK_NULL_HANDLE)
			vkDestroyDevice(device, nullptr);
	}
	
	bool Device::init(PhysicalDevice *phys_dev)
	{
		priority = 1.0f;
		
		/*int present;
		int graphic;
		
		phys_dev.getFirstValidQueueFamily(surface, &present, &graphic);*/
		vector<VkDeviceQueueCreateInfo> queue_create_infos;
		int tmp[] = {}; // 	{phys_dev->getPresentIndex(), phys_dev->getGraphicIndex()};
		
		for (int i = 0; i < 2; i++)
		{
			VkDeviceQueueCreateInfo queue_create_info = {};
			queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queue_create_info.queueFamilyIndex = tmp[i];
			queue_create_info.queueCount = 1;
			queue_create_info.pQueuePriorities = &priority;
			queue_create_infos.push_back(queue_create_info);
		}

		VkDeviceCreateInfo device_create_infos = {};
		device_create_infos.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_create_infos.pQueueCreateInfos = queue_create_infos.data();
		device_create_infos.queueCreateInfoCount = queue_create_infos.size();
		device_create_infos.pEnabledFeatures = phys_dev->getFeatures();
		
		//device_create_infos.enabledExtensionCount = 0;
		//device_create_infos.enabledLayerCount = 0;
		
		// C'est la que ca plante
		// segfault
		if (vkCreateDevice(phys_dev->getVulkanObject(), &device_create_infos, nullptr, &device) != VK_SUCCESS)
		{
		    cerr << "Failed to create logical device." << endl;
		    return false;
		}
		
		vkGetDeviceQueue(device, phys_dev->getGraphicIndex(), 0, &graphic_device_queue);
		vkGetDeviceQueue(device, phys_dev->getPresentIndex(), 0, &present_device_queue);
		/*if (vkGetDeviceQueue(device, phys_dev.getFirstValidQueueFamily(), 0, &device_queue) != VK_SUCCESS)
		{
		    cerr << "Failed to create queue." << endl;
		    return false;
		}*/
		
		return true;
	}
}
