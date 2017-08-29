#ifndef IMAGE_H
	#define IMAGE_H
	
	#include <vulkan/vulkan.h>
	
	#include <Device.h>
	
	#include <commands/SingleCommandBuffer.h>
	
	namespace GEngine
	{
		class Image
		{
			private:
				VkImage m_image;
				VkFormat m_format;
				VkImageLayout m_layout;
				uint32_t m_width;
				uint32_t m_height;
				
				Device *device;
			public:
				Image(Device *dev);
				Image(Device *dev, VkImage image);
				~Image();
				
				bool createImage(uint32_t width, uint32_t height, VkFormat format);
				bool createImage(uint32_t width, uint32_t height, VkFormat format, VkImageLayout layout, VkImageUsageFlags usage);
				void destroyImage();
				
				VkImage *getVulkanObject();
				
				void transitionImageLayout(VkImageLayout new_layout, SingleCommandBuffer *command_buffer);
				void copyFromBuffer(Buffer *buffer, SingleCommandBuffer *command_buffer);
		};
	}
	
#endif

