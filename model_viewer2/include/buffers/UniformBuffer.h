#ifndef UNIFORMBUFFEROBJECT_H_INCLUDED
#define UNIFORMBUFFEROBJECT_H_INCLUDED
#include<glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <buffers/Buffer.h>

namespace GEngine
{
    class UniformBuffer : public Buffer
    {
        public:
            glm::mat4 model;
            glm::mat4 viewproj;
            bool allocBuffer();
            bool createBuffer(unsigned long buffer_size);
            void createDescriptorSetLayout();
            void update();

        private:

    };
}


#endif // UNIFORMBUFFEROBJECT_H_INCLUDED
