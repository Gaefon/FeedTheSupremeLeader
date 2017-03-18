#ifndef SWAP_CHAIN_H
#define SWAP_CHAIN_H

#include <Surface.h>
#include <Window.h>
#include <Device.h>

#include <vector>

namespace GEngine
{
	class SwapChain
	{
		private:
			VkSwapchainKHR swap_chain;
			VkExtent2D extent;
			VkSurfaceFormatKHR surface_format;
			
			Device *logical_device;
			
			
		public:
			SwapChain(Surface *surface, Window *window, PhysicalDevice *phys_dev, Device *dev);
			~SwapChain();
			
			std::vector<VkImage> getImages();
	};
}

#endif
