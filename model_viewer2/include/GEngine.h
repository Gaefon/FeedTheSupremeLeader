#ifndef G_ENGINE_H
#define G_ENGINE_H

#include <string>
#include <list>

#include <vulkan/vulkan.h>

#include <PhysicalDevice.h>


namespace GEngine
{
	class Engine
	{
		private:
			VkInstance vulkan_instance;
			VkApplicationInfo app_info;
			VkInstanceCreateInfo create_info;
			
			std::list<PhysicalDevice *> physical_devices;
			
			bool init(std::string app_name, int version);
	
		public:
			Engine(std::string app_name, int version);
			~Engine();
			
			VkInstance getVulkanObject();
			bool pickPhysicalDevices();
			const std::list<PhysicalDevice *> getListPhysicalDevices();
		
	};
}

#endif
