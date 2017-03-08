#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H

#include <vulkan/vulkan.h>

namespace GEngine
{
	class PhysicalDevice
	{
		private:
			VkPhysicalDevice physical_device;
			VkPhysicalDeviceProperties properties;
			VkPhysicalDeviceFeatures features;
			
		public:
			PhysicalDevice();
			PhysicalDevice(VkPhysicalDevice instance);
			~PhysicalDevice();
			
			bool isSuitable();
			int getFirstValidQueueFamily();
			
			VkPhysicalDevice getVulkanObject();
			const VkPhysicalDeviceFeatures *getFeatures();
			
			int getApiVersion();
			int getDriverVersion();
			int getVendorId();
			int getDeviceId();
			char *getDeviceName();
	};
}

#endif
