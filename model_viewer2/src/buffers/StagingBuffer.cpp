#include <buffers/StagingBuffer.h>

#include <iostream>

#include <string.h>

using namespace std;

namespace GEngine
{
	StagingBuffer::StagingBuffer(Device *dev) : Buffer(dev){}

	StagingBuffer::~StagingBuffer() {}

	bool StagingBuffer::createBuffer(unsigned long buffer_size)
	{
		VkBufferCreateInfo buffer_info = {};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = buffer_size;
		buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		size = buffer_size;

		if (vkCreateBuffer(device->getVulkanObject(), &buffer_info, nullptr, &buffer) != VK_SUCCESS)
		{
			cerr << "failed to create vertex buffer" << endl;
			return false;
		}

		return true;
	}

	bool StagingBuffer::allocBuffer()
	{
		VkMemoryRequirements mem_requirements;
		VkPhysicalDeviceMemoryProperties mem_properties;

		vkGetBufferMemoryRequirements(device->getVulkanObject(), buffer, &mem_requirements);
		vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice()->getVulkanObject(), &mem_properties);

		VkMemoryAllocateInfo alloc_infos = {};
		alloc_infos.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_infos.allocationSize = mem_requirements.size;
        alloc_infos.memoryTypeIndex = findSuitableMemory(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &mem_properties);

		if (vkAllocateMemory(device->getVulkanObject(), &alloc_infos, nullptr, &dev_memory) != VK_SUCCESS)
		{
			cerr << "failed to allocate memory" << endl;
			return false;
		}
		return true;
	}

	void StagingBuffer::addVertexData(vector<uint16_t> *indexes)
	{
		addData(indexes->data(), indexes->size() * sizeof(uint16_t));
		nb_vertices = indexes->size();
	}
	
	void StagingBuffer::addData(void *data, size_t data_size)
	{
		void *buffer_data;
		vkMapMemory(device->getVulkanObject(), dev_memory, 0, size, 0, &buffer_data);
		memcpy(buffer_data, data, data_size);
		vkUnmapMemory(device->getVulkanObject(), dev_memory);
	}
}
