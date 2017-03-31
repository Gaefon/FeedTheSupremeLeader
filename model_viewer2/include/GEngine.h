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
			std::vector<const char *> validation_layers;
			
			VkDebugReportCallbackEXT debug_callback;
			bool validation_layers_enabled;
			
			
			bool checkValidationLayerSupport();
			void createValidationCallback();
	
		public:
			Engine();
			~Engine();
			
			bool init(std::string app_name, int version);
			void enableValidationLayers();
			
			void addExtension(std::string name);
			std::list<std::string> getExtensions();
			
			VkInstance getVulkanObject();
			bool pickPhysicalDevices();
			const std::list<PhysicalDevice *> getListPhysicalDevices();
		
	};
}

#endif
