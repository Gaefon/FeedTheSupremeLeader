#include <VertexBuffer.h>

#include <iostream>

#include <string.h>

using namespace std;

namespace GEngine
{
	VertexBuffer::VertexBuffer(Device *dev)
	{
		vertex_buffer = VK_NULL_HANDLE;
		dev_memory = VK_NULL_HANDLE;
		device = dev;
		nb_vertices = 0;
	}
	
	VertexBuffer::~VertexBuffer()
	{
		if (vertex_buffer != VK_NULL_HANDLE)
			vkDestroyBuffer(device->getVulkanObject(), vertex_buffer, nullptr);
		if (dev_memory != VK_NULL_HANDLE)
			vkFreeMemory(device->getVulkanObject(), dev_memory, nullptr);
	}
	
	
	bool VertexBuffer::createBuffer(unsigned long buffer_size)
	{
		VkBufferCreateInfo buffer_info = {};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = buffer_size;
		buffer_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		size = buffer_size;
		
		if (vkCreateBuffer(device->getVulkanObject(), &buffer_info, nullptr, &vertex_buffer) != VK_SUCCESS)
		{
			cerr << "failed to create vertex buffer" << endl;
			return false;
		}
		
		return true;
	}
	
	unsigned int VertexBuffer::findSuitableMemory(unsigned int filter, VkMemoryPropertyFlags flags, VkPhysicalDeviceMemoryProperties *mem_properties)
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
	
	bool VertexBuffer::allocBuffer()
	{
		VkMemoryRequirements mem_requirements;
		VkPhysicalDeviceMemoryProperties mem_properties;
		
		vkGetBufferMemoryRequirements(device->getVulkanObject(), vertex_buffer, &mem_requirements);
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
	
	void VertexBuffer::bindToDevice()
	{
		vkBindBufferMemory(device->getVulkanObject(), vertex_buffer, dev_memory, 0);
	}
	
	void VertexBuffer::addVertexData(vector<Vertex> *vertices)
	{
		void *data;
		vkMapMemory(device->getVulkanObject(), dev_memory, 0, size, 0, &data);
		memcpy(data, vertices->data(), size);
		vkUnmapMemory(device->getVulkanObject(), dev_memory);
		nb_vertices = vertices->size();
	}
	
	VkBuffer VertexBuffer::getVulkanBuffer()
	{
		return vertex_buffer;
	}
	
	unsigned int VertexBuffer::getNbVertices()
	{
		return nb_vertices;
	}
	
}
