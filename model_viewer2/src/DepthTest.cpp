#include <DepthTest.h>
#include <iostream>

using namespace std;

namespace GEngine
{
	DepthTest::DepthTest(Device *dev) : depth_image(dev)
	{
		device = dev;
		depth_image_view = nullptr;
	}
	
	DepthTest::~DepthTest()
	{
		if (depth_image_view != nullptr)
		{
			vkFreeMemory(device->getVulkanObject(), depth_image_memory, nullptr);
			delete depth_image_view;
		}
		depth_image.destroyImage();
	}
	
	bool DepthTest::createDepthTest(SwapChain *sw, CommandPool *pool)
	{
		unsigned int width = sw->getExtent().width;
		unsigned int height = sw->getExtent().height;
		VkFormat depth_format = findDepthFormat();
		
		depth_image.createImage(width, height, depth_format);
		
		VkMemoryRequirements mem_requirements;
		vkGetImageMemoryRequirements(device->getVulkanObject(), *(depth_image.getVulkanObject()), &mem_requirements);

		VkMemoryAllocateInfo alloc_info = {};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = findMemoryType(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		if (vkAllocateMemory(device->getVulkanObject(), &alloc_info, nullptr, &depth_image_memory) != VK_SUCCESS)
		{
			cerr << "failed to allocate image memory!" << endl;
			return false;
		}

        vkBindImageMemory(device->getVulkanObject(), *(depth_image.getVulkanObject()), depth_image_memory, 0);
		
		depth_image_view = new ImageView(device, &depth_image, depth_format, VK_IMAGE_ASPECT_DEPTH_BIT);
		
		
		SingleCommandBuffer cmd(device);
		cmd.createCommandBuffer(pool);
		cmd.begin();
		
		VkImageAspectFlags aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT;

		if (hasStencilComponent(depth_format))
			aspect_mask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		
		depth_image.transitionImageLayout(VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, &cmd, aspect_mask);
		cmd.end();
		cmd.submit();
		
		return true;
	}
	
	VkFormat DepthTest::findSupportedFormat(VkImageTiling tiling, VkFormatFeatureFlags features)
	{
		vector<VkFormat> candidates = {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT};
		
		for (vector<VkFormat>::iterator it = candidates.begin(); it != candidates.end(); ++it)
		{
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(device->getPhysicalDevice()->getVulkanObject(), *it, &props);

			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
				return *it;
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
				return *it;
		}
		cerr << "failed to find supported format!" << endl;
		
		return VK_FORMAT_UNDEFINED;
	}
	
	unsigned int DepthTest::findMemoryType(unsigned int type_filter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties mem_properties;
		vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice()->getVulkanObject(), &mem_properties);

		for (unsigned int i = 0; i < mem_properties.memoryTypeCount; i++)
		{
			if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
				return i;
		}

		cerr << "failed to find suitable memory type!" << endl;

		return -1;
    }
	
	VkFormat DepthTest::findDepthFormat()
	{
		return findSupportedFormat(VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}
	
	bool DepthTest::hasStencilComponent(VkFormat format)
	{
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}
	
	ImageView *DepthTest::getImageView()
	{
		return depth_image_view;
	}

}
