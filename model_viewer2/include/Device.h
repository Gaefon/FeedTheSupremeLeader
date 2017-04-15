#ifndef DEVICE_H
#define DEVICE_H

#include <list>
#include <string>

#include <vulkan/vulkan.h>
#include <PhysicalDevice.h>

namespace GEngine
{
	class Device
	{
		private:
			VkDevice device;
			VkPhysicalDeviceFeatures device_features;
			
			PhysicalDevice *physical_device;
			
			VkQueue present_device_queue;
			VkQueue graphic_device_queue;
			float priority;
			
			
		
		public:
			Device(PhysicalDevice *phys_dev);
			~Device();
			
			bool init(std::list<std::string> extensions);
			
			PhysicalDevice *getPhysicalDevice();
			
			VkDevice getVulkanObject();
			
			VkQueue getGraphicQueue();
			VkQueue getPresentQueue();
			
			void waitIdle();
	};
}

#endif
