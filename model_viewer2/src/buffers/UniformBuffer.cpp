#include <buffers/Buffer.h>
#include <iostream>
#include <string.h>

using namespace std;

namespace GEngine
{
    UniformBuffer::createDescriptorSetLayout()
    {
        VkDescriptorSetLayoutBinding ubo_layout_binding = {};
        ubo_layout_binding.binding = 0;
        ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        ubo_layout_binding.descriptorCount = 1;
        ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        ubo_layout_binding.pImmutableSamplers = nullptr;

        VkDescriptorSetLayout descriptor_set_layout;
        VkPipelineLayout pipeline_layout;

        VkDescriptorSetLayoutCreateInfo layout_info = {};
        layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layout_info.bindingCount = 1;
        layout_info.pBindings = &ubo_layout_binding;


		if (vkCreateDescriptorSetLayout(device->getVulkanObject(), &layout_info, nullptr, &descriptor_set_layout) != VK_SUCCESS)
		{
			cerr << "failed to create descriptor set" << endl;
			return false;
		}

		VkPipelineLayoutCreateInfo pipeline_layout_info = {};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 1;
		pipeline_layout_info.pSetLayouts = &descriptor_set_layout;

    }

    bool UniformBuffer::createBuffer(unsigned int buffer_size)
    {
        VkBufferCreateInfo buffer_info = {};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = buffer_size;
        buffer_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		size = buffer_size;

		if (vkCreateBuffer(device->getVulkanObject(), &buffer_info, nullptr, &buffer) != VK_SUCCESS)
		{
			cerr << "failed to create uniform buffer" << endl;
			return false;
		}
        return true;
    }

    bool UniformBuffer::allocBuffer()
	{
		VkMemoryRequirements mem_requirements;
		VkPhysicalDeviceMemoryProperties mem_properties;

		vkGetBufferMemoryRequirements(device->getVulkanObject(), buffer, &mem_requirements);
		vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice()->getVulkanObject(), &mem_properties);

		VkMemoryAllocateInfo alloc_infos = {};
		alloc_infos.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_infos.allocationSize = mem_requirements.size;
        alloc_infos.memoryTypeIndex = findSuitableMemory(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &mem_properties);

		if (vkAllocateMemory(device->getVulkanObject(), &alloc_infos, nullptr, &dev_memory) != VK_SUCCESS)
		{
			cerr << "failed to allocate memory" << endl;
			return false;
		}
		return true;
	}

}
