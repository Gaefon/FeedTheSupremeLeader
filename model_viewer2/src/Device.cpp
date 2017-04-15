#include <Device.h>

#include <iostream>
#include <set>
#include <vector>

using namespace std;

namespace GEngine
{
	Device::Device(PhysicalDevice *phys_dev)
	{
		physical_device = phys_dev;
		device = VK_NULL_HANDLE;
	}
	
	Device::~Device()
	{
		if (device != VK_NULL_HANDLE)
			vkDestroyDevice(device, nullptr);
	}
	
	bool Device::init(list<string> extensions)
	{
		priority = 1.0f;
		
		/*int present;
		int graphic;
		
		phys_dev.getFirstValidQueueFamily(surface, &present, &graphic);*/
		vector<VkDeviceQueueCreateInfo> queue_create_infos;
		unsigned int tmp[] = {physical_device->getPresentIndex(), physical_device->getGraphicIndex()};
		
		cout << "present index " << physical_device->getPresentIndex() << endl;
		cout << "graphic index " << physical_device->getGraphicIndex() << endl;
		
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
		device_create_infos.pEnabledFeatures = physical_device->getFeatures();
		
		const char **exts = new const char*[extensions.size()];
		int i = 0;
		
		for (list<string>::iterator it = extensions.begin(); it != extensions.end(); it++)
		{
			exts[i] = (*it).c_str();
			i++;
		}
		
		device_create_infos.enabledExtensionCount = extensions.size();
		device_create_infos.ppEnabledExtensionNames = exts;
		
		//device_create_infos.enabledExtensionCount = 0;
		//device_create_infos.enabledLayerCount = 0;
		
		if (vkCreateDevice(physical_device->getVulkanObject(), &device_create_infos, nullptr, &device) != VK_SUCCESS)
		{
		    cerr << "Failed to create logical device." << endl;
		    delete exts;
		    return false;
		}
		
		vkGetDeviceQueue(device, physical_device->getGraphicIndex(), 0, &graphic_device_queue);
		vkGetDeviceQueue(device, physical_device->getPresentIndex(), 0, &present_device_queue);
		
		delete exts;
		return true;
	}
	
	VkDevice Device::getVulkanObject()
	{
		return device;
	}
	
	VkQueue Device::getGraphicQueue()
	{
		return graphic_device_queue;
	}
	
	VkQueue Device::getPresentQueue()
	{
		return present_device_queue;
	}
	
	void Device::waitIdle()
	{
		vkDeviceWaitIdle(device);
	}
	
	PhysicalDevice *Device::getPhysicalDevice()
	{
		return physical_device;
	}
}
