#include <PhysicalDevice.h>

#include <string.h>

#include <vector>
#include <iostream>

using namespace std;

namespace GEngine
{
	PhysicalDevice::PhysicalDevice()
	{
		physical_device = VK_NULL_HANDLE;
		present_idx = -1;
	}
	
	PhysicalDevice::PhysicalDevice(VkPhysicalDevice instance)
	{
		memcpy(&physical_device, &instance, sizeof(VkPhysicalDevice));
		vkGetPhysicalDeviceProperties(physical_device, &properties);
		vkGetPhysicalDeviceFeatures(physical_device, &features);
	}
	
	PhysicalDevice::~PhysicalDevice()
	{}
	
	
	bool PhysicalDevice::isSuitable(std::list<std::string> exts)
	{
		for (list<string>::iterator it = exts.begin(); it != exts.end(); it++)
		{
			if (!supportExtension(*it))
				return false;
		}
		
		return properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && features.geometryShader;
	}
	
	vector<string> PhysicalDevice::getSupportedExtension()
	{
		unsigned int extension_count = 0;
		
		vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, nullptr);
		
		vector<VkExtensionProperties> extensions(extension_count);
		vector<string> ext_str(extension_count);
		vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, extensions.data());
		
		for (const VkExtensionProperties& extension: extensions)
			ext_str.push_back(string(extension.extensionName));
		
		return ext_str;
	}
	
	bool PhysicalDevice::supportExtension(string name)
	{
		for (string ext_name : getSupportedExtension())
		{
			if (ext_name.compare(name))
				return true;
		}
		return false;
	}
	
	void PhysicalDevice::setPresentIndex(int idx)
	{
		present_idx = idx;
	}
	
	void PhysicalDevice::setGraphicIndex(int idx)
	{
		graphic_index = idx;
	}
	
	int PhysicalDevice::getPresentIndex()
	{
		return present_idx;
	}
	
	int PhysicalDevice::getGraphicIndex()
	{
		return graphic_index;
	}
	
	
	VkPhysicalDevice PhysicalDevice::getVulkanObject()
	{
		return physical_device;
	}
	
	const VkPhysicalDeviceFeatures *PhysicalDevice::getFeatures()
	{
		return &features;
	}
	
	int PhysicalDevice::getApiVersion()
	{
		return properties.apiVersion;
	}
	
	int PhysicalDevice::getDriverVersion()
	{
		return properties.driverVersion;
	}
	
	int PhysicalDevice::getVendorId()
	{
		return properties.vendorID;
	}
	
	int PhysicalDevice::getDeviceId()
	{
		return properties.deviceID;
	}
	
	char *PhysicalDevice::getDeviceName()
	{
		return properties.deviceName;
	}
}
