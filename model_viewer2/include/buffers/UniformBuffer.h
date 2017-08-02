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
            void setMatrix(glm::mat4 mv, glm::mat4 proj);
            VkDescriptorSetLayout *getDescriptorSetLayout();
        private:
			typedef struct s_uniformBufferObject
			{
				glm::mat4 modelview;
				glm::mat4 projection;
			} UniformBufferObject;
			
			UniformBufferObject buffer_data;
			VkDescriptorSetLayout descriptor_set_layout;
    };
}


#endif // UNIFORMBUFFEROBJECT_H_INCLUDED
