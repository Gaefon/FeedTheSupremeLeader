#include <GEngine.h>
#include <Const.h>

#include <iostream>
#include <vector>


namespace GEngine
{
	using namespace std;
	
	Engine::Engine(string app_name, int version)
	{
		vulkan_instance = VK_NULL_HANDLE;
		logical_dev = nullptr;
		
		if (!init(app_name, version))
			vulkan_instance = VK_NULL_HANDLE;
	}
	
	Engine::~Engine()
	{
		if (logical_dev != nullptr)
			delete logical_dev;
		
		// free all the physical devices !
		for (PhysicalDevice *dev: physical_devices)
			delete dev;
		physical_devices.clear();
			
		if (vulkan_instance != VK_NULL_HANDLE)
			vkDestroyInstance(vulkan_instance, nullptr);
		
	}

	bool Engine::init(string app_name, int version)
	{
		unsigned int device_count = 0;
		
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pNext = nullptr;
		app_info.pApplicationName = app_name.c_str();
		app_info.applicationVersion = version;
		
		app_info.pEngineName = Const::ENGINE_NAME.c_str();
		app_info.engineVersion = Const::ENGINE_VERSION;
		app_info.apiVersion = VK_API_VERSION_1_0;
		
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pNext = nullptr;
		create_info.pApplicationInfo = &app_info;
		
		create_info.enabledExtensionCount = 0;
		create_info.ppEnabledExtensionNames = nullptr;
		create_info.enabledLayerCount = 0;
		
		VkResult result = vkCreateInstance(&create_info, nullptr, &vulkan_instance);
		
		if (result != VK_SUCCESS)
		{
			cerr << "Failed to init vulkan. (res: " << result << ")" << endl;
			return false;
		}
		
		if (vkEnumeratePhysicalDevices(vulkan_instance, &device_count, nullptr) != VK_SUCCESS)
		{
			cerr << "Failed to get number of physical devices. No GPU compatible with Vulkan." << endl;
			return false;
		}
		
		vector<VkPhysicalDevice> devices(device_count);
		if (vkEnumeratePhysicalDevices(vulkan_instance, &device_count, devices.data()) != VK_SUCCESS)
		{
			cerr << "Failed to fetch physical devices." << endl;
			return false;
		}
		
		for (unsigned int i = 0; i < devices.size(); i++)
			physical_devices.push_back(new PhysicalDevice(devices.at(i)));
		
		for (PhysicalDevice *dev: physical_devices)
		{
			if (dev->isSuitable() && dev->getFirstValidQueueFamily() >= 0)
			{
				logical_dev = new Device(*dev);
				break;
			}
		}
		
		return true;
	}
	
	bool Engine::pickPhysicalDevice()
	{
		return true;
	}
	
	const std::list<PhysicalDevice *> Engine::getListPhysicalDevices()
	{
		return physical_devices;
	}
}
