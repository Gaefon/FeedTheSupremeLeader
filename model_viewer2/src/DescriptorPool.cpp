#include <DescriptorPool.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	DescriptorPool::DescriptorPool()
	{
	}
	
	DescriptorPool::~DescriptorPool()
	{
		if (descriptor_pool != VK_NULL_HANDLE)
			vkDestroyDescriptorPool(device->getVulkanObject(), descriptor_pool, nullptr);
	}
	
	bool DescriptorPool::createDescriptorPool(Device *dev)
	{
		device = dev;
		
		VkDescriptorPoolSize pool_size = {};
		pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		pool_size.descriptorCount = 1;

		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.poolSizeCount = 1;
		pool_info.pPoolSizes = &pool_size;
		pool_info.maxSets = 1;
		
		if (vkCreateDescriptorPool(dev->getVulkanObject(), &pool_info, nullptr, &descriptor_pool) != VK_SUCCESS)
		{
			cerr << "failed to create descriptor pool!" << endl;
			return false;
		}
		
		return true;
	}
	
	VkDescriptorPool *DescriptorPool::getVulkanObject()
	{
		return &descriptor_pool;
	}
}