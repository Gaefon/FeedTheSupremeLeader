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
			
			std::list<PhysicalDevice *> physical_devices;
			
			std::list<std::string> list_extension;
			
			bool init(std::string app_name, int version);
	
		public:
			Engine(std::string app_name, int version);
			~Engine();
			
			void addExtension(std::string name);
			std::list<std::string> getExtensions();
			
			VkInstance getVulkanObject();
			bool pickPhysicalDevices();
			const std::list<PhysicalDevice *> getListPhysicalDevices();
		
	};
}

#endif
