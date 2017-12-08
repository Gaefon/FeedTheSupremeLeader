#include <commands/CommandPool.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	CommandPool::CommandPool(Device *dev)
	{
		command_pool = VK_NULL_HANDLE;
		device = dev;
	}
	
	CommandPool::~CommandPool()
	{
		if (command_pool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(device->getVulkanObject(), command_pool, nullptr);
		}
	}
	
	void CommandPool::createCommandPool()
	{
		VkCommandPoolCreateInfo pool_create_infos = {};
		pool_create_infos.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_create_infos.queueFamilyIndex = device->getPhysicalDevice()->getGraphicIndex();
		pool_create_infos.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		if (vkCreateCommandPool(device->getVulkanObject(), &pool_create_infos, nullptr, &command_pool) != VK_SUCCESS)
		{
			command_pool = VK_NULL_HANDLE;
			cerr << "Failed to create command pool" << endl;
		}
	}
	
	VkCommandPool CommandPool::getVulkanObject()
	{
		return command_pool;
	}
}
