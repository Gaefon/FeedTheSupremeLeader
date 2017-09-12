#include <VertexBufferData.h>
using namespace std;

namespace GEngine
{
    VkVertexInputBindingDescription *VertexBufferData::getBindingDescription()
    {
        VkVertexInputBindingDescription *binding_description = new VkVertexInputBindingDescription{0, sizeof(VertexBufferData), VK_VERTEX_INPUT_RATE_VERTEX};
        return binding_description;
    }

    array<VkVertexInputAttributeDescription, 3> *VertexBufferData::getAttributeDescriptions()
    {
		array<VkVertexInputAttributeDescription, 3> *attributeDescriptions = new array<VkVertexInputAttributeDescription, 3>();
		//array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
		attributeDescriptions->at(0).binding = 0;
		attributeDescriptions->at(0).location = 0;
		attributeDescriptions->at(0).format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions->at(0).offset = offsetof(VertexBufferData, v_position);
		
		attributeDescriptions->at(1).binding = 0;
		attributeDescriptions->at(1).location = 1;
		attributeDescriptions->at(1).format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions->at(1).offset = offsetof(VertexBufferData, v_color);
		
		attributeDescriptions->at(2).binding = 0;
		attributeDescriptions->at(2).location = 2;
		attributeDescriptions->at(2).format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions->at(2).offset = offsetof(VertexBufferData, v_uv);
		
		return attributeDescriptions;
    }
}
