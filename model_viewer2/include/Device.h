#ifndef DEVICE_H
#define DEVICE_H

#include <vulkan/vulkan.h>

#include <PhysicalDevice.h>

namespace GEngine
{
	class Device
	{
		private:
			VkDevice device;
			VkPhysicalDeviceFeatures device_features;
			VkDeviceCreateInfo device_create_infos;
			
			VkQueue device_queue;
			VkDeviceQueueCreateInfo queue_create_info;
			float priority;
			
			
			bool init(PhysicalDevice phys_dev);
		
		public:
			Device(PhysicalDevice phys_dev);
			~Device();
	};
}

#endif
