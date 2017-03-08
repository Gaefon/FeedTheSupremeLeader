#include <PhysicalDevice.h>

#include <string.h>

#include <vector>

using namespace std;

namespace GEngine
{
	PhysicalDevice::PhysicalDevice()
	{
		physical_device = VK_NULL_HANDLE;
	}
	
	PhysicalDevice::PhysicalDevice(VkPhysicalDevice instance)
	{
		memcpy(&physical_device, &instance, sizeof(VkPhysicalDevice));
		vkGetPhysicalDeviceProperties(physical_device, &properties);
		vkGetPhysicalDeviceFeatures(physical_device, &features);
	}
	
	PhysicalDevice::~PhysicalDevice()
	{}
	
	
	bool PhysicalDevice::isSuitable()
	{
		VkPhysicalDeviceProperties dev_properties;
		VkPhysicalDeviceFeatures dev_features;
		
		vkGetPhysicalDeviceProperties(physical_device, &dev_properties);
		vkGetPhysicalDeviceFeatures(physical_device, &dev_features);
		
		return dev_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && dev_features.geometryShader;
	}
	
	int PhysicalDevice::getFirstValidQueueFamily()
	{
		unsigned int queue_family_count = 0;
		
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
		
		vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());
		
		int i = 0;
		
		for (VkQueueFamilyProperties queue: queue_families)
		{
			if (queue.queueCount > 0 && queue.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				break;
			i++;
		}
		
		return i;
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
