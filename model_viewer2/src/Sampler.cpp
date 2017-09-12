#include <Sampler.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	Sampler::Sampler(Device *dev)
	{
		device = dev;
		m_sampler = VK_NULL_HANDLE;
		createSampler();
	}
	
	Sampler::~Sampler()
	{
		if (m_sampler != VK_NULL_HANDLE)
			vkDestroySampler(device->getVulkanObject(), m_sampler, nullptr);
	}
	
	void Sampler::createSampler()
	{
		VkSamplerCreateInfo sampler_info = {};
		sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		sampler_info.magFilter = VK_FILTER_LINEAR;
		sampler_info.minFilter = VK_FILTER_LINEAR;
		sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		
		sampler_info.anisotropyEnable = VK_TRUE;
		sampler_info.maxAnisotropy = 16;

		sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		sampler_info.unnormalizedCoordinates = VK_FALSE;
		sampler_info.compareEnable = VK_FALSE;
		sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
		sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		sampler_info.mipLodBias = 0.0f;
		sampler_info.minLod = 0.0f;
		sampler_info.maxLod = 0.0f;
		
		if (vkCreateSampler(device->getVulkanObject(), &sampler_info, nullptr, &m_sampler) != VK_SUCCESS)
		{
			m_sampler = VK_NULL_HANDLE;
			cerr << "failed to create texture sampler!" << endl;
		}
	}
	
	VkSampler *Sampler::getVulkanObject()
	{
		return &m_sampler;
	}
}
