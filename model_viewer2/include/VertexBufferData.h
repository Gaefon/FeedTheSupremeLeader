#ifndef VERTEX_H
#define VERTEX_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace GEngine
{
    struct VertexBufferData
    {
	    glm::vec3 v_position;
	    glm::vec3 v_color;
	    glm::vec2 v_uv;
	    glm::vec3 v_normal;
	    
		static VkVertexInputBindingDescription *getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 4> *getAttributeDescriptions();

    };
}
#endif
