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
		        
		        void createImageViewKHR(Image *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat);
		    public:
		    	ImageView(Device *dev);
		        ImageView(Device *dev, Image *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat);
		        ImageView(Device *dev, Image *vkImage, VkFormat format, VkImageAspectFlags aspect_flags);
		        ~ImageView();
		        
		        void createImageView(Image *vkImage, VkFormat format, VkImageAspectFlags aspect_flags);
		        
		        VkImageView getVulkanObject();
		};
	}

#endif // IMAGEVIEW_H
