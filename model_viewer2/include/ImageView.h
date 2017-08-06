#ifndef IMAGEVIEW_H
	#define IMAGEVIEW_H

	#include <Device.h>
	#include <Image.h>

	namespace GEngine
	{
		class ImageView
		{
		    private:
		        VkImageView image_view;
		        Device *device;
		        
		        void createImageViewKHR(Device *device, Image *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat);
		        void createImageView(Device *device, Image *vkImage, VkFormat format, VkImageAspectFlags aspect_flags);
		    public:
		        ImageView(Device *device, Image *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat);
		        ImageView(Device *device, Image *vkImage, VkFormat format, VkImageAspectFlags aspect_flags);
		        ~ImageView();
		        VkImageView getVulkanObject();
		};
	}

#endif // IMAGEVIEW_H
