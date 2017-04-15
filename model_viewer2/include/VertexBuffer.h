#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vulkan/vulkan.h>

#include <Device.h>
#include <Vertex.h>

namespace GEngine
{
	class VertexBuffer
	{
		private:
			VkBuffer vertex_buffer;
			VkDeviceMemory dev_memory;
			Device *device;
			size_t size;
			unsigned int nb_vertices;
			
			unsigned int findSuitableMemory(unsigned int filter, VkMemoryPropertyFlags flags, VkPhysicalDeviceMemoryProperties *mem_properties);
			
		public:
			VertexBuffer(Device *dev);
			~VertexBuffer();
			
			bool createBuffer(unsigned long buffer_size);
			bool allocBuffer();
			void bindToDevice();
			void addVertexData(std::vector<Vertex> *vertices);
			
			VkBuffer getVulkanBuffer();
			unsigned int getNbVertices();
	};
}

#endif
