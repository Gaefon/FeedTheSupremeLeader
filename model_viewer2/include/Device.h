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
			
			VkQueue present_device_queue;
			VkQueue graphic_device_queue;
			float priority;
			
			
		
		public:
			Device();
			~Device();
			
			bool init(PhysicalDevice *phys_dev, std::list<std::string> extensions);
			
			VkDevice getVulkanObject();
			
			VkQueue getGraphicQueue();
			VkQueue getPresentQueue();
			
			void waitIdle();
	};
}

#endif
