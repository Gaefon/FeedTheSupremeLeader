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

			virtual bool createBuffer(unsigned long buffer_size, VkBufferUsageFlags usage_flags);
            virtual bool allocBuffer(VkMemoryPropertyFlags memory_flags);
			virtual void bindToDevice();
			void addVertexData(std::vector<VertexBufferData> *vertices);
			virtual void setNbVertices(unsigned int nb);

			virtual VkBuffer getVulkanBuffer();
			virtual unsigned int getNbVertices();
	};
}



#endif // BUFFER_H_INCLUDED
