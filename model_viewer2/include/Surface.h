#ifndef SURFACE_H
#define SURFACE_H

#include <vulkan/vulkan.h>

#include <GEngine.h>
#include <Window.h>
#include <PhysicalDevice.h>

namespace GEngine
{
	class Surface
	{
		private:
			VkSurfaceKHR surface;
			
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> present_modes;
			
			bool init(Engine *engine, Window *window);
		
		public:
			Surface(Engine *instance, Window *window);
			~Surface();
			
			VkSurfaceKHR getVulkanObject();
			PhysicalDevice *getSuitableDevice(Engine *instance);
			void getFirstValidQueueFamily(PhysicalDevice *physical_device, int *graphic, int *present);
			
			bool isDeviceCompatible(PhysicalDevice *dev);
			VkSurfaceFormatKHR chooseSwapSurfaceFormat();
			VkPresentModeKHR chooseSwapPresentMode();
			VkExtent2D chooseSwapExtent(Window *window);
			VkSurfaceCapabilitiesKHR getCapabilities();

	};
}

#endif
