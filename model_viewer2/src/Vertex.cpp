#include <Vertex.h>
using namespace std;

namespace GEngine
{
    Vertex::Vertex(glm::vec2 position, glm::vec3 color)
    {
        v_position = position;
        v_color = color;
    }

    Vertex::~Vertex(){}

    VkVertexInputBindingDescription *Vertex::getBindingDescription()
    {
        VkVertexInputBindingDescription *binding_description = new VkVertexInputBindingDescription{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX};
        return binding_description;
    }

    array<VkVertexInputAttributeDescription, 2> &Vertex::getAttributeDescriptions()
    {
		//array<VkVertexInputAttributeDescription, 2> *attributeDescriptions = new array<VkVertexInputAttributeDescription, 2>();
		array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, v_position);
		
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, v_color);
		
		return attributeDescriptions;
    }
}
