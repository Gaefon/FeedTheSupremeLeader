#ifndef VERTEX_H
#define VERTEX_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace GEngine
{
    struct Vertex
    {
	    glm::vec3 v_position;
	    glm::vec3 v_color;
	    
		static VkVertexInputBindingDescription *getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 2> *getAttributeDescriptions();

    };
}
#endif
