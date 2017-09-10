#include <buffers/Buffer.h>

#include <iostream>

#include <string.h>

using namespace std;

namespace GEngine
{
	Buffer::Buffer(Device *dev)
	{
		buffer = VK_NULL_HANDLE;
		dev_memory = VK_NULL_HANDLE;
		device = dev;
		nb_vertices = 0;
		size = 0;
	}

	Buffer::~Buffer()
	{
		cleanup();
	}
	
	void Buffer::cleanup()
	{
		if (buffer != VK_NULL_HANDLE)
			vkDestroyBuffer(device->getVulkanObject(), buffer, nullptr);
		if (dev_memory != VK_NULL_HANDLE)
			vkFreeMemory(device->getVulkanObject(), dev_memory, nullptr);
	}

	bool Buffer::createBuffer(unsigned long buffer_size, VkBufferUsageFlags usage_flags)
	{
		VkBufferCreateInfo buffer_info = {};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = buffer_size;
        buffer_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		if(usage_flags != VK_NULL_HANDLE)
        {
            buffer_info.usage = usage_flags;
        }
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		size = buffer_size;

		if (vkCreateBuffer(device->getVulkanObject(), &buffer_info, nullptr, &buffer) != VK_SUCCESS)
		{
			cerr << "failed to create buffer" << endl;
			return false;
		}

		return true;
	}

	unsigned int Buffer::findSuitableMemory(unsigned int filter, VkMemoryPropertyFlags flags, VkPhysicalDeviceMemoryProperties *mem_properties)
	{
		for (unsigned int i = 0; i < mem_properties->memoryTypeCount; i++)
		{
			if (filter & (1 << i) && (mem_properties->memoryTypes[i].propertyFlags & flags) == flags)
			{
				return i;
			}
		}

		return -1;
	}

	bool Buffer::allocBuffer(VkMemoryPropertyFlags memory_flags)
	{
		VkMemoryRequirements mem_requirements;
		VkPhysicalDeviceMemoryProperties mem_properties;

		vkGetBufferMemoryRequirements(device->getVulkanObject(), buffer, &mem_requirements);
		vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice()->getVulkanObject(), &mem_properties);

		VkMemoryAllocateInfo alloc_infos = {};
		alloc_infos.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_infos.allocationSize = mem_requirements.size;
        if(memory_flags != VK_NULL_HANDLE)
        {
            alloc_infos.memoryTypeIndex = findSuitableMemory(mem_requirements.memoryTypeBits, memory_flags, &mem_properties);
        }
        else
        {
            alloc_infos.memoryTypeIndex = findSuitableMemory(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &mem_properties);
        }

		if (vkAllocateMemory(device->getVulkanObject(), &alloc_infos, nullptr, &dev_memory) != VK_SUCCESS)
		{
			cerr << "failed to allocate memory" << endl;
			return false;
		}
		return true;
	}

	void Buffer::bindToDevice()
	{
		vkBindBufferMemory(device->getVulkanObject(), buffer, dev_memory, 0);
	}

	void Buffer::addVertexData(vector<VertexBufferData> *vertices)
	{
		void *data;
		vkMapMemory(device->getVulkanObject(), dev_memory, 0, size, 0, &data);
		memcpy(data, vertices->data(), size);
		vkUnmapMemory(device->getVulkanObject(), dev_memory);
		nb_vertices = vertices->size();
	}


	VkBuffer Buffer::getVulkanBuffer()
	{
		return buffer;
	}
	
	VkDeviceMemory *Buffer::getVulkanDeviceMemory()
	{
		return &dev_memory;
	}

	unsigned int Buffer::getNbVertices()
	{
		return nb_vertices;
	}

    void Buffer::setNbVertices(unsigned int nb)
	{
		nb_vertices = nb;
	}
	
	size_t Buffer::getBufferSize()
	{
		return size;
	}

}
