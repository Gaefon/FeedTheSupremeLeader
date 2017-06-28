#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vulkan/vulkan.h>
#include <buffers/Buffer.h>
#include <Device.h>
#include <Vertex.h>

namespace GEngine
{
	class VertexBuffer : public Buffer
	{
        public:
            VertexBuffer(Device *dev);
            virtual ~VertexBuffer();
            bool createBuffer(unsigned long buffer_size);
            bool allocBuffer();
	};
}

#endif
