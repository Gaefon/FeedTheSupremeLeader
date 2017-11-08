#include <Image.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	Image::Image(Device *dev)
	{
		device = dev;
		m_image = VK_NULL_HANDLE;
	}
	
	Image::Image(Device *dev, VkImage image)
	{
		device = dev;
		m_image = image;
		//memcpy(&m_image, &image, sizeof(VkImage));
	}
	
	Image::~Image()
	{
	}
	
	bool Image::createImage(uint32_t width, uint32_t height, VkFormat format)
	{
		return createImage(width, height, format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}
	
	bool Image::createImage(uint32_t width, uint32_t height, VkFormat format, VkImageLayout layout, VkImageUsageFlags usage)
	{
		// create the image
		m_format = format;
		m_layout = layout;
		m_width = width;
		m_height = height;
		
		VkImageCreateInfo image_info = {};
		image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_info.imageType = VK_IMAGE_TYPE_2D;
		image_info.extent.width = width;
		image_info.extent.height = height;
		image_info.extent.depth = 1;
		image_info.mipLevels = 1;
		image_info.arrayLayers = 1;
		image_info.format = format;
		image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
		
		image_info.initialLayout = layout; //VK_IMAGE_LAYOUT_PREINITIALIZED; // 
		image_info.usage = usage; //VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		
		image_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateImage(device->getVulkanObject(), &image_info, nullptr, &m_image) != VK_SUCCESS)
		{
			cerr << "failed to create image!" << endl;
			return false;
		}
	
		return true;
	}
	
	void Image::destroyImage()
	{
		if (m_image != VK_NULL_HANDLE)
		{
			vkDestroyImage(device->getVulkanObject(), m_image, nullptr);
		}
	}
	
	void Image::bindToBuffer(Buffer *buffer)
	{
		VkMemoryRequirements mem_requirements;
		vkGetImageMemoryRequirements(device->getVulkanObject(), m_image, &mem_requirements);
		
		VkPhysicalDeviceMemoryProperties properties;
		//device->getPhysicalDevice()->getMemoryProperties(&properties);
		vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice()->getVulkanObject(), &properties);

		VkMemoryAllocateInfo alloc_info = {};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = buffer->findSuitableMemory(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &properties);

		if (vkAllocateMemory(device->getVulkanObject(), &alloc_info, nullptr, buffer->getVulkanDeviceMemory()) != VK_SUCCESS)
			cerr << "failed to allocate image memory!" << endl;
		
		vkBindImageMemory(device->getVulkanObject(), m_image, *(buffer->getVulkanDeviceMemory()), 0);
	}
	
	VkImage *Image::getVulkanObject()
	{
		return &m_image;
	}
	
	
	
	void Image::reinitLayout()
	{
		m_layout = VK_IMAGE_LAYOUT_UNDEFINED;
	}
	
	void Image::transitionImageLayout(VkImageLayout new_layout, SingleCommandBuffer *command_buffer)
	{
		transitionImageLayout(new_layout, command_buffer, VK_IMAGE_ASPECT_COLOR_BIT);
	}
	
	void Image::transitionImageLayout(VkImageLayout new_layout, SingleCommandBuffer *command_buffer, VkImageAspectFlags aspect_mask)
	{
		VkPipelineStageFlags source_stage;
		VkPipelineStageFlags destination_stage;
		VkImageMemoryBarrier barrier = {};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = m_layout;
		barrier.newLayout = new_layout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = m_image;
		barrier.subresourceRange.aspectMask = aspect_mask;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;
		
		if (m_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;		
		}
		else if (m_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			source_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (m_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destination_stage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		}
		else
		{
			cout << "else" << endl;
			barrier.srcAccessMask = 0; // TODO
			barrier.dstAccessMask = 0; // TODO
		}
		
		vkCmdPipelineBarrier(*(command_buffer->getVulkanObject()), source_stage, destination_stage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
		
		m_layout = new_layout;
		
	}
	
	void Image::copyFromBuffer(Buffer *buffer, SingleCommandBuffer *command_buffer)
	{
		VkBufferImageCopy region = {};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;

		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;

		region.imageOffset = {0, 0, 0};
		region.imageExtent = {m_width, m_height, 1};
		
		vkCmdCopyBufferToImage(*(command_buffer->getVulkanObject()), buffer->getVulkanBuffer(), m_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	}
	
}
