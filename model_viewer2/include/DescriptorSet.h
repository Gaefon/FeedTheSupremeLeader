#ifndef DESCRIPTOR_SET_H
	#define DESCRIPTOR_SET_H
	
	#include <vulkan/vulkan.h>
	#include <DescriptorPool.h>
	#include <buffers/UniformBuffer.h>
	#include <Device.h>
	#include <models/Texture.h>
	
	namespace GEngine
	{
		class DescriptorSet
		{
			private:
				VkDescriptorSet descriptor_set;
				
				Device *device;
				
			public:
				DescriptorSet();
				~DescriptorSet();
				
				bool createDescriptorSet(Device *dev, DescriptorPool *desc_pool, VkDescriptorSetLayout *descriptor_set_layouts);
				void updateDescriptorSet(UniformBuffer *buffer, Texture *tex, size_t size);
				
				VkDescriptorSet *getVulkanObject();
		};
	}
	
#endif
