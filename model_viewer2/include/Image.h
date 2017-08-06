#ifndef IMAGE_H
	#define IMAGE_H
	
	#include <vulkan/vulkan.h>
	
	#include <Device.h>
	
	namespace GEngine
	{
		class Image
		{
			private:
				VkImage m_image;
				
				Device *device;
			public:
				Image(Device *dev);
				Image(Device *dev, VkImage image);
				~Image();
				
				bool createImage();
				
				VkImage *getVulkanObject();
		};
	}
	
#endif

