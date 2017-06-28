#ifndef INDEXBUFFER_H_INCLUDED
#define INDEXBUFFER_H_INCLUDED
#include <vulkan/vulkan.h>
#include <buffers/Buffer.h>
#include <Device.h>
#include <Vertex.h>
namespace GEngine
{
	class IndexBuffer : public Buffer
	{
        public:
            IndexBuffer(Device *dev);
            virtual ~IndexBuffer();
            bool createBuffer(unsigned long buffer_size);
            bool allocBuffer();
	};
}


#endif // INDEXBUFFER_H_INCLUDED
