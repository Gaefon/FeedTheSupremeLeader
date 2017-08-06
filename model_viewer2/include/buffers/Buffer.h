#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <vulkan/vulkan.h>

#include <Device.h>
#include <VertexBufferData.h>

namespace GEngine
{
	class Buffer
	{
		protected:
            VkBuffer buffer;
			VkDeviceMemory dev_memory;
			unsigned int nb_vertices;
			unsigned int findSuitableMemory(unsigned int filter, VkMemoryPropertyFlags flags, VkPhysicalDeviceMemoryProperties *mem_properties);
			size_t size;
			Device *device;

		public:
			Buffer(Device *dev);
			~Buffer();

			void cleanup();
			bool createBuffer(unsigned long buffer_size, VkBufferUsageFlags usage_flags);
            bool allocBuffer(VkMemoryPropertyFlags memory_flags);
			void bindToDevice();
			void addVertexData(std::vector<VertexBufferData> *vertices);
			virtual void setNbVertices(unsigned int nb);

			VkBuffer getVulkanBuffer();
			unsigned int getNbVertices();
			size_t getBufferSize();
	};
}



#endif // BUFFER_H_INCLUDED
