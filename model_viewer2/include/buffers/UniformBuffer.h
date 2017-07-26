#ifndef UNIFORMBUFFEROBJECT_H_INCLUDED
#define UNIFORMBUFFEROBJECT_H_INCLUDED
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <buffers/Buffer.h>
#include <buffers/Framebuffers.h>

namespace GEngine
{
    class UniformBuffer : public Buffer
    {
        public:
            UniformBuffer(Device *dev);
            ~UniformBuffer();
            bool allocBuffer();
            bool createBuffer(unsigned long buffer_size);
            void createDescriptorSetLayout();
            void update();
        private:
            glm::mat4 model;
            glm::mat4 viewproj;
            
            
			typedef struct s_uniformBufferObject
			{
				glm::mat4 modelview;
				glm::mat4 projection;
			} UniformBufferObject;
    };
}


#endif // UNIFORMBUFFEROBJECT_H_INCLUDED
