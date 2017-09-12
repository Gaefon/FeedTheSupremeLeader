#ifndef SAMPLER_H
	#define SAMPLER_H
	
	#include <Device.h>
	#include <vulkan/vulkan.h>
	
	namespace GEngine
	{
		class Sampler
		{
			private:
				Device *device;				
				VkSampler m_sampler;
				
				void createSampler();
			public:
				Sampler(Device *dev);
				~Sampler();
				
				VkSampler *getVulkanObject();
				
		};
	}
	
#endif
