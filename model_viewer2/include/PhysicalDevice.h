#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H

#include <vulkan/vulkan.h>

#include <list>
#include <vector>
#include <string>

namespace GEngine
{
	class PhysicalDevice
	{
		private:
			VkPhysicalDevice physical_device;
			VkPhysicalDeviceProperties properties;
			VkPhysicalDeviceFeatures features;
			
			int present_idx;
			int graphic_index;
			
		public:
			PhysicalDevice();
			PhysicalDevice(VkPhysicalDevice instance);
			~PhysicalDevice();
			
			bool isSuitable(std::list<std::string> exts);
			
			std::vector<std::string> getSupportedExtension();
			bool supportExtension(std::string name);
			
			void setPresentIndex(int idx);
			void setGraphicIndex(int idx);
			
			int getPresentIndex();
			int getGraphicIndex();
			
			//void getFirstValidQueueFamily(int *graphic, int *present);
			
			VkPhysicalDevice getVulkanObject();
			const VkPhysicalDeviceFeatures *getFeatures();
			
			int getApiVersion();
			int getDriverVersion();
			int getVendorId();
			int getDeviceId();
			char *getDeviceName();
	};
}

#endif
