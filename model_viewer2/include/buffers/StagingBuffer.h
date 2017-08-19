#ifndef STAGINGBUFFER_H_INCLUDED
#define STAGINGBUFFER_H_INCLUDED
#include <vulkan/vulkan.h>
#include <buffers/Buffer.h>
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
            void addData(void *data, size_t data_size);
	};
}



#endif // STAGINGBUFFER_H_INCLUDED
