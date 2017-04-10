#ifndef VERTEX_H
#define VERTEX_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace GEngine
{
    class Vertex
    {
        public:
            Vertex(glm::vec2 position, glm::vec3 color);
            ~Vertex();
            VkVertexInputBindingDescription *getBindingDescription();
            std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();

        private:
            glm::vec2 v_position;
            glm::vec3 v_color;

    };
}
#endif
