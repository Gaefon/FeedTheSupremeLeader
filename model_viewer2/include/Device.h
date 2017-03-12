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
			VkDeviceCreateInfo device_create_infos;
			
			VkQueue device_queue;
			float priority;
			
			
			bool init(Surface surface, PhysicalDevice phys_dev);
		
		public:
			Device(Surface surface, PhysicalDevice phys_dev);
			~Device();
	};
}

#endif
