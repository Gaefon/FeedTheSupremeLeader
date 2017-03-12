#ifndef SURFACE_H
#define SURFACE_H

#include <vulkan/vulkan.h>

#include <GEngine.h>
#include <Window.h>

namespace GEngine
{
	class Surface
	{
		private:
			VkSurfaceKHR surface;
			
			bool init(Engine *engine, Window *window);
		
		public:
			Surface(Engine *instance, Window *window);
			~Surface();
			
			VkSurfaceKHR getVulkanObject();
			PhysicalDevice *getSuitableDevice(Engine *instance);
			void getFirstValidQueueFamily(PhysicalDevice *physical_device, int *graphic, int *present);
	};
}

#endif
