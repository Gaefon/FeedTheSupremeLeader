#include <CommandBuffers.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	CommandBuffers::CommandBuffers()
	{
		command_pool = VK_NULL_HANDLE;
		device = nullptr;
	}
	
	CommandBuffers::~CommandBuffers()
	{
		if (command_pool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(device->getVulkanObject(), command_pool, nullptr);
		}
		
		
	}
	
	void CommandBuffers::createCommandPool(Device *dev, PhysicalDevice *phys_dev)
	{
		VkCommandPoolCreateInfo pool_create_infos = {};
		pool_create_infos.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_create_infos.queueFamilyIndex = phys_dev->getGraphicIndex();
		pool_create_infos.flags = 0;
		
		device = dev;
		
		if (vkCreateCommandPool(device->getVulkanObject(), &pool_create_infos, nullptr, &command_pool) != VK_SUCCESS)
		{
			command_pool = VK_NULL_HANDLE;
			cerr << "Failed to create command pool" << endl;
		}
	}
	
	void CommandBuffers::createCommandBuffers(Framebuffers *frame_buffers)
	{
		command_buffers.resize(frame_buffers->getSize(), VK_NULL_HANDLE);
		
		
		VkCommandBufferAllocateInfo command_buffer_alloc_infos = {};
		command_buffer_alloc_infos.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		command_buffer_alloc_infos.commandPool = command_pool;
		command_buffer_alloc_infos.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		command_buffer_alloc_infos.commandBufferCount = command_buffers.size();
		
		
		if (vkAllocateCommandBuffers(device->getVulkanObject(), &command_buffer_alloc_infos, command_buffers.data()) != VK_SUCCESS)
		{
			cerr << "Error allocating command buffers" << endl;
		}
	}
	
	void CommandBuffers::startRecording()
	{
		for (unsigned int i = 0; i < command_buffers.size(); i++)
		{
			VkCommandBufferBeginInfo begin_info = {};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			begin_info.pInheritanceInfo = nullptr;
			
			vkBeginCommandBuffer(command_buffers[i], &begin_info);
		}
	}
}
