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
				
			public:
				Sampler(Device *dev);
				~Sampler();
				
				void createSampler();
		};
	}
	
#endif
