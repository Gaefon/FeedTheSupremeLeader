#ifndef DESCRIPTOR_POOL_H
	#define DESCRIPTOR_POOL_H
	
	#include <Device.h>
	
	#include <vulkan/vulkan.h>
	
	namespace GEngine
	{
		class DescriptorPool
		{
			private:
				VkDescriptorPool descriptor_pool;
				
				Device *device;
				
			public:
				DescriptorPool();
				~DescriptorPool();
				bool createDescriptorPool(Device *dev);
				VkDescriptorPool *getVulkanObject();
		};
	}
	
	
#endif
