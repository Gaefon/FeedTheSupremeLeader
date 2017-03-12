#include <PhysicalDevice.h>

#include <string.h>

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
	
	
	bool PhysicalDevice::isSuitable()
	{
		return properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && features.geometryShader;
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
