#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <Device.h>

#include <vulkan/vulkan.h>

namespace GEngine
{
	class Semaphore
	{
		private:
			VkSemaphore semaphore;
			Device *device;
			
		public:
			Semaphore();
			~Semaphore();
			
			VkSemaphore getVulkanObject();
			
			void createSemaphore(Device *dev);
	};
}

#endif
