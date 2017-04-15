#include <GEngine.h>
#include <Const.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <strings.h>

using namespace std;

namespace GEngine
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType,
	uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
	{
		(void) flags;
		(void) objType;
		(void) obj;
		(void) location;
		(void) code;
		(void) layerPrefix;
		(void) userData;
	
		cerr << "validation layer : " << msg << endl;
		return VK_FALSE;
	}

	Engine::Engine()
	{
		vulkan_instance = VK_NULL_HANDLE;
		debug_callback = VK_NULL_HANDLE;
		validation_layers_enabled = false;
	}
	
	Engine::~Engine()
	{
		delete device;
	
		// free all the physical devices !
		for (PhysicalDevice *dev: physical_devices)
			delete dev;
		physical_devices.clear();
		
		if (debug_callback != VK_NULL_HANDLE)
		{
			PFN_vkDestroyDebugReportCallbackEXT function_ptr = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(vulkan_instance, "vkDestroyDebugReportCallbackEXT");
			if (function_ptr != nullptr)
				function_ptr(vulkan_instance, debug_callback, nullptr);
		}
			
		if (vulkan_instance != VK_NULL_HANDLE)
			vkDestroyInstance(vulkan_instance, nullptr);
		
	}

	bool Engine::init(string app_name, int version)
	{
		const char **extensions;
		unsigned int nb;
		vector<const char *> data_ext;
		
		VkInstanceCreateInfo create_info = {};
		VkApplicationInfo app_info = {};
		
		//memset(&create_info, 0, sizeof(VkInstanceCreateInfo));
		//memset(&app_info, 0, sizeof(VkApplicationInfo));
		
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
		
		extensions = glfwGetRequiredInstanceExtensions(&nb);
		
		for (unsigned int i = 0; i < nb; i++)
			data_ext.push_back(extensions[i]);
		
		if (validation_layers_enabled)
			data_ext.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		
		create_info.enabledExtensionCount = data_ext.size();
		create_info.ppEnabledExtensionNames = data_ext.data();
		
		if (validation_layers_enabled)
		{
			create_info.enabledLayerCount = validation_layers.size();
			create_info.ppEnabledLayerNames = validation_layers.data();
		}
		else
			create_info.enabledLayerCount = 0;
		
		VkResult result = vkCreateInstance(&create_info, nullptr, &vulkan_instance);
		
		if (result != VK_SUCCESS)
		{
			cerr << "Failed to init vulkan. (res: " << result << ")" << VK_ERROR_EXTENSION_NOT_PRESENT << endl;
			vulkan_instance = VK_NULL_HANDLE;
			return false;
		}
		
		//delete arr_dat;
		createValidationCallback();
		
		return true;
	}
	
	bool Engine::checkValidationLayerSupport()
	{	
		unsigned int layer_count;
		vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

		vector<VkLayerProperties> available_layers(layer_count);
		vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
		
		for (string layer_name : validation_layers)
		{
			bool layer_found = false;
			for (const VkLayerProperties& layer_properties : available_layers)
			{
				if (layer_name.compare(layer_properties.layerName) == 0)
				{
					layer_found = true;
					break;
				}
			}

			if (!layer_found)
				return false;
		}

		return true;
	}
	
	void Engine::enableValidationLayers()
	{
		validation_layers.push_back("VK_LAYER_LUNARG_standard_validation");
		
		validation_layers_enabled = true;
		
		if (!checkValidationLayerSupport())
		{
			cerr << "Validation layers are not supported :'(. Validation layers deactivated." << endl;
			validation_layers_enabled = false;
		}
	}
	
	void Engine::createValidationCallback()
	{
		if (validation_layers_enabled)
		{
			VkDebugReportCallbackCreateInfoEXT create_info = {};
			create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			create_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
			create_info.pfnCallback = debugCallback;
			
			PFN_vkCreateDebugReportCallbackEXT function_ptr = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(vulkan_instance, "vkCreateDebugReportCallbackEXT");
			if (function_ptr != nullptr)
			{
				if (function_ptr(vulkan_instance, &create_info, nullptr, &debug_callback) != VK_SUCCESS)
				{
					cerr << "Failed to create debug callback" << endl;
				}
			}
		}
	}
	
	void Engine::addExtension(string name)
	{
		list_extension.push_back(name);
	}
	
	list<string> Engine::getExtensions()
	{
		return list_extension;
	}
	
	bool Engine::pickPhysicalDevices()
	{
		unsigned int device_count = 0;
		
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
			
		return true;
	}
	
	const list<PhysicalDevice *> Engine::getListPhysicalDevices()
	{
		return physical_devices;
	}
	
	bool Engine::createLogicalDevice(PhysicalDevice *dev)
	{
		device = new Device(dev);
		return device->init(getExtensions());
	}
	
	Device *Engine::getLogicalDevice()
	{
		return device;
	}
	
	VkInstance Engine::getVulkanObject()
	{
		return vulkan_instance;
	}
}
