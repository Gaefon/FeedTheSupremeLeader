#include <commands/SingleCommandBuffer.h>

namespace GEngine
{
	SingleCommandBuffer::SingleCommandBuffer(Device *dev)
	{
		command_buffer = VK_NULL_HANDLE;
		device = dev;
	}
	
	SingleCommandBuffer::~SingleCommandBuffer()
	{
	}
	
	void SingleCommandBuffer::createCommandBuffer(CommandPool *command_pool)
	{
		VkCommandBufferAllocateInfo alloc_info = {};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		alloc_info.commandPool = command_pool->getVulkanObject();
		alloc_info.commandBufferCount = 1;

		vkAllocateCommandBuffers(device->getVulkanObject(), &alloc_info, &command_buffer);
	}
	
	void SingleCommandBuffer::begin()
	{
		VkCommandBufferBeginInfo begin_info = {};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(command_buffer, &begin_info);
	}
	
	void SingleCommandBuffer::end()
	{
		vkEndCommandBuffer(command_buffer);
	}
	
	void SingleCommandBuffer::submit()
	{
		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.commandBufferCount = 1;
		submit_info.pCommandBuffers = &command_buffer;
		
		vkQueueSubmit(device->getGraphicQueue(), 1, &submit_info, VK_NULL_HANDLE);
	}
	
	void SingleCommandBuffer::copyBuffers(Buffer *src, Buffer *dst, VkDeviceSize size)
	{
		VkBufferCopy copy_region = {};
		copy_region.size = size;
		vkCmdCopyBuffer(command_buffer, src->getVulkanBuffer(), dst->getVulkanBuffer(), 1, &copy_region);
	}
	
	VkCommandBuffer *SingleCommandBuffer::getVulkanObject()
	{
		return &command_buffer;
	}
	
}
