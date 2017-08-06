#include <DepthTest.h>
#include <iostream>

using namespace std;

namespace GEngine
{
	DepthTest::DepthTest(Device *dev)
	{
		device = dev;
		depth_image_view = nullptr;
	}
	
	DepthTest::~DepthTest()
	{
		if (depth_image_view != nullptr)
		{
			//delete depth_image_view;
			vkDestroyImage(device->getVulkanObject(), depth_image, nullptr);
			vkFreeMemory(device->getVulkanObject(), depth_image_memory, nullptr);
		}
	}
	
	bool DepthTest::createDepthTest(SwapChain *sw)
	{
		unsigned int width = sw->getExtent().width;
		unsigned int height = sw->getExtent().height;
		VkFormat depth_format = findDepthFormat();
		
		// create the image
		VkImageCreateInfo image_info = {};
		image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_info.imageType = VK_IMAGE_TYPE_2D;
		image_info.extent.width = width;
		image_info.extent.height = height;
		image_info.extent.depth = 1;
		image_info.mipLevels = 1;
		image_info.arrayLayers = 1;
		image_info.format = depth_format;
		image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
		image_info.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
		image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		image_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        
        if (vkCreateImage(device->getVulkanObject(), &image_info, nullptr, &depth_image) != VK_SUCCESS)
        {
			cerr << "failed to create image!" << endl;
			return false;
		}
		
		VkMemoryRequirements mem_requirements;
		vkGetImageMemoryRequirements(device->getVulkanObject(), depth_image, &mem_requirements);

		VkMemoryAllocateInfo alloc_info = {};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = findMemoryType(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		if (vkAllocateMemory(device->getVulkanObject(), &alloc_info, nullptr, &depth_image_memory) != VK_SUCCESS)
		{
			cerr << "failed to allocate image memory!" << endl;
			return false;
		}

        vkBindImageMemory(device->getVulkanObject(), depth_image, depth_image_memory, 0);
		
		depth_image_view = new ImageView(device, &depth_image, depth_format, VK_IMAGE_ASPECT_DEPTH_BIT);
		
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

}
