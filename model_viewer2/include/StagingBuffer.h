#ifndef STAGINGBUFFER_H_INCLUDED
#define STAGINGBUFFER_H_INCLUDED
#include <vulkan/vulkan.h>
#include <Buffer.h>
#include <Device.h>

namespace GEngine
{
	class StagingBuffer : public Buffer
	{
        public:
            using Buffer::addVertexData;
            StagingBuffer(Device *dev);
            virtual ~StagingBuffer();
            bool createBuffer(unsigned long buffer_size);
            bool allocBuffer();
            void addVertexData(std::vector<uint16_t> *indexes);
	};
}



#endif // STAGINGBUFFER_H_INCLUDED
