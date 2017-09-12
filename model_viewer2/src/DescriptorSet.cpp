#include <DescriptorSet.h>

#include <iostream>
#include <array>

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
	
	void DescriptorSet::updateDescriptorSet(UniformBuffer *buffer, Texture *tex, size_t size)
	{
		VkDescriptorBufferInfo buffer_info = {};
		buffer_info.buffer = buffer->getVulkanBuffer();
		buffer_info.offset = 0;
		buffer_info.range = size;
		
		VkDescriptorImageInfo image_info = {};
		image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		image_info.imageView = tex->getImageView()->getVulkanObject();
		image_info.sampler = *(tex->getSampler()->getVulkanObject());
		
		array<VkWriteDescriptorSet, 2> descriptor_write = {};
		
		descriptor_write[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptor_write[0].dstSet = descriptor_set;
		descriptor_write[0].dstBinding = 0;
		descriptor_write[0].dstArrayElement = 0;
		descriptor_write[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptor_write[0].descriptorCount = 1;
		descriptor_write[0].pBufferInfo = &buffer_info;
		descriptor_write[0].pImageInfo = nullptr;
		descriptor_write[0].pTexelBufferView = nullptr;
		
		descriptor_write[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptor_write[1].dstSet = descriptor_set;
		descriptor_write[1].dstBinding = 1;
		descriptor_write[1].dstArrayElement = 0;
		descriptor_write[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptor_write[1].descriptorCount = 1;
		descriptor_write[1].pImageInfo = &image_info;
		
		vkUpdateDescriptorSets(device->getVulkanObject(), descriptor_write.size(), descriptor_write.data(), 0, nullptr);
		
	}
	
	VkDescriptorSet *DescriptorSet::getVulkanObject()
	{
		return &descriptor_set;
	}
}
