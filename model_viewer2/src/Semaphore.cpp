#include <Semaphore.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	Semaphore::Semaphore()
	{
		semaphore = VK_NULL_HANDLE;
		device = nullptr;
	}
	
	Semaphore::~Semaphore()
	{
		destroySemaphore();
	}
	
	VkSemaphore Semaphore::getVulkanObject()
	{
		return semaphore;
	}
	
	void Semaphore::createSemaphore(Device *dev)
	{
		VkSemaphoreCreateInfo semaphore_info = {};
		semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		device = dev;
		
		if (vkCreateSemaphore(device->getVulkanObject(), &semaphore_info, nullptr, &semaphore) != VK_SUCCESS)
		{
			semaphore = VK_NULL_HANDLE;
			cerr << "Failed to create semaphore" << endl;
		}
	}
	
	void Semaphore::destroySemaphore()
	{
		if (device != nullptr && semaphore != VK_NULL_HANDLE)
		{
			vkDestroySemaphore(device->getVulkanObject(), semaphore, nullptr);
			semaphore = VK_NULL_HANDLE;
		}
	}
}
