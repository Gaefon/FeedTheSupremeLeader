#include <buffers/IndexBuffer.h>

#include <iostream>

#include <string.h>

using namespace std;

namespace GEngine
{
    IndexBuffer::IndexBuffer(Device *dev) : Buffer(dev){}

	IndexBuffer::~IndexBuffer() {}

	bool IndexBuffer::createBuffer(unsigned long buffer_size)
	{
		VkBufferCreateInfo buffer_info = {};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = buffer_size;
        buffer_info.usage =  VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		size = buffer_size;

		if (vkCreateBuffer(device->getVulkanObject(), &buffer_info, nullptr, &buffer) != VK_SUCCESS)
		{
			cerr << "failed to create index buffer" << endl;
			return false;
		}

		return true;
	}

	bool IndexBuffer::allocBuffer()
	{
		VkMemoryRequirements mem_requirements;
		VkPhysicalDeviceMemoryProperties mem_properties;

		vkGetBufferMemoryRequirements(device->getVulkanObject(), buffer, &mem_requirements);
		vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice()->getVulkanObject(), &mem_properties);

		VkMemoryAllocateInfo alloc_infos = {};
		alloc_infos.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_infos.allocationSize = mem_requirements.size;
        alloc_infos.memoryTypeIndex = findSuitableMemory(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &mem_properties);

		if (vkAllocateMemory(device->getVulkanObject(), &alloc_infos, nullptr, &dev_memory) != VK_SUCCESS)
		{
			cerr << "failed to allocate memory" << endl;
			return false;
		}
		return true;
	}
}
