#ifndef DEPTH_TEST_H
	#define DEPTH_TEST_H
	
	#include <vector>
	#include <vulkan/vulkan.h>
	#include <Device.h>
	#include <SwapChain.h>
	#include <Image.h>
	#include <ImageView.h>
	
	namespace GEngine
	{
		class DepthTest
		{
			private:
				Device *device;
				
				VkDeviceMemory depth_image_memory;
				Image depth_image;
				ImageView *depth_image_view;
				
				VkFormat findSupportedFormat(VkImageTiling tiling, VkFormatFeatureFlags features);
				bool hasStencilComponent(VkFormat format);
				unsigned int findMemoryType(unsigned int type_filter, VkMemoryPropertyFlags properties);
			public:
				DepthTest(Device *dev);
				~DepthTest();
				
				VkFormat findDepthFormat();
				bool createDepthTest(SwapChain *sw, CommandPool *pool);
				
				ImageView *getImageView();
		};
	}
	
#endif
