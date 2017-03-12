#ifndef DEVICE_H
#define DEVICE_H

#include <vulkan/vulkan.h>

#include <PhysicalDevice.h>
#include <Surface.h>

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
			
			
			bool init(PhysicalDevice *phys_dev);
		
		public:
			Device(PhysicalDevice *phys_dev);
			~Device();
	};
}

#endif
