#ifndef COMMAND_POOL_H
	#define COMMAND_POOL_H
	
	#include <vulkan/vulkan.h>
	
	#include <Device.h>
	
	namespace GEngine
	{
		class CommandPool
		{
			private:
				VkCommandPool command_pool;
				Device *device;
			public:
				CommandPool(Device *device);
				~CommandPool();
				void createCommandPool();
				VkCommandPool getVulkanObject();
		};
	}
	
#endif
