#include <DescriptorSet.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	DescriptorSet::DescriptorSet()
	{
	}
	
	DescriptorSet::~DescriptorSet()
	{
	}
	
	bool DescriptorSet::createDescriptorSet(Device *dev, DescriptorPool *desc_pool, VkDescriptorSetLayout *descriptor_set_layouts)
	{
		device = dev;
		
		VkDescriptorSetLayout layouts[] = {*descriptor_set_layouts};
		VkDescriptorSetAllocateInfo alloc_info = {};
		
		alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		alloc_info.descriptorPool = *(desc_pool->getVulkanObject());
		alloc_info.descriptorSetCount = 1;
		alloc_info.pSetLayouts = layouts;
		
		if (vkAllocateDescriptorSets(dev->getVulkanObject(), &alloc_info, &descriptor_set) != VK_SUCCESS)
		{
			cerr << "Failed to create descriptor set" << endl;
			return false;
		}
		return true;
	}
	
	void DescriptorSet::updateDescriptorSet(UniformBuffer *buffer, size_t size)
	{
		VkDescriptorBufferInfo buffer_info = {};
		buffer_info.buffer = buffer->getVulkanBuffer();
		buffer_info.offset = 0;
		buffer_info.range = size;
		
		VkWriteDescriptorSet descriptor_write = {};
		descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptor_write.dstSet = descriptor_set;
		descriptor_write.dstBinding = 0;
		descriptor_write.dstArrayElement = 0;
		descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptor_write.descriptorCount = 1;
		descriptor_write.pBufferInfo = &buffer_info;
		descriptor_write.pImageInfo = nullptr;
		descriptor_write.pTexelBufferView = nullptr;
		
		vkUpdateDescriptorSets(device->getVulkanObject(), 1, &descriptor_write, 0, nullptr);
		
	}
	
	VkDescriptorSet *DescriptorSet::getVulkanObject()
	{
		return &descriptor_set;
	}
}
