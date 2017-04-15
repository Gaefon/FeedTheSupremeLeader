#include <Vertex.h>
using namespace std;

namespace GEngine
{
    VkVertexInputBindingDescription *Vertex::getBindingDescription()
    {
        VkVertexInputBindingDescription *binding_description = new VkVertexInputBindingDescription{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX};
        return binding_description;
    }

    array<VkVertexInputAttributeDescription, 2> *Vertex::getAttributeDescriptions()
    {
		array<VkVertexInputAttributeDescription, 2> *attributeDescriptions = new array<VkVertexInputAttributeDescription, 2>();
		//array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
		attributeDescriptions->at(0).binding = 0;
		attributeDescriptions->at(0).location = 0;
		attributeDescriptions->at(0).format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions->at(0).offset = offsetof(Vertex, v_position);
		
		attributeDescriptions->at(1).binding = 0;
		attributeDescriptions->at(1).location = 1;
		attributeDescriptions->at(1).format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions->at(1).offset = offsetof(Vertex, v_color);
		
		return attributeDescriptions;
    }
}
