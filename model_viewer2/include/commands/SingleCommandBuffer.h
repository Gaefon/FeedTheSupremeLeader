#ifndef SINGLE_COMMAND_BUFFER_H
	#define SINGLE_COMMAND_BUFFER_H

	#include <vulkan/vulkan.h>	
	#include <Device.h>
	#include <commands/CommandPool.h>
	#include <buffers/Buffer.h>
	
	namespace GEngine
	{
		class SingleCommandBuffer
		{
			private:
				VkCommandBuffer command_buffer;
				Device *device;
			public:
				SingleCommandBuffer(Device *dev);
				~SingleCommandBuffer();
				
				void createCommandBuffer(CommandPool *command_pool);
				void begin();
				void end();
				void submit();
				void copyBuffers(Buffer *src, Buffer *dst, VkDeviceSize size);
				
				VkCommandBuffer *getVulkanObject();
		};
	}
	
	
#endif
