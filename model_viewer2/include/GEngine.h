#include <string>
#include <list>

#include <vulkan/vulkan.h>

#include <PhysicalDevice.h>
#include <Device.h>

#ifndef G_ENGINE_H
#define G_ENGINE_H

namespace GEngine
{
	class Engine
	{
		private:
			VkInstance vulkan_instance;
			VkApplicationInfo app_info;
			VkInstanceCreateInfo create_info;
			
			std::list<PhysicalDevice *> physical_devices;
			Device *logical_dev;
			
			bool init(std::string app_name, int version);
			bool pickPhysicalDevice();
	
		public:
			Engine(std::string app_name, int version);
			~Engine();
			
			const std::list<PhysicalDevice *> getListPhysicalDevices();
		
	};
}

#endif
