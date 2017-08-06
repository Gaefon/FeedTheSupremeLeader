#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <Device.h>

namespace GEngine
{
    class ImageView
    {
        private:
            VkImageView image_view;
            Device *device;
            
            void createImageViewKHR(Device *device, VkImage *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat);
            void createImageView(Device *device, VkImage *vkImage, VkFormat format, VkImageAspectFlags aspect_flags);
        public:
            ImageView(Device *device, VkImage *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat);
            ImageView(Device *device, VkImage *vkImage, VkFormat format, VkImageAspectFlags aspect_flags);
            ~ImageView();
            VkImageView getVulkanObject();
    };
}

#endif // IMAGEVIEW_H
