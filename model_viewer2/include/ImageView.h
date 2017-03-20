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
        public:
            ImageView(VkImage *vkImage, VkSurfaceFormatKHR *vkSurfaceFormat, Device *device);
            ~ImageView();
            VkImageView getVulkanObject();
    };
}

#endif // IMAGEVIEW_H
