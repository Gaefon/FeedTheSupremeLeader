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
			
			void destroySemaphore();
			
		public:
			Semaphore();
			~Semaphore();
			
			VkSemaphore getVulkanObject();
			
			void createSemaphore(Device *dev);
			bool isAllocated();
	};
}

#endif
