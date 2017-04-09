#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include <vulkan/vulkan.h>

#include <Device.h>
#include <SwapChain.h>

namespace GEngine
{
	class RenderPass
	{
		private:
			VkRenderPass render_pass;
			
			Device *logical_device;
		public:
			RenderPass(Device *dev);
			~RenderPass();
			
			bool initRenderPass(SwapChain *swap_chain);
			
			VkRenderPass getVulkanObject();
			
			void startRenderPass();
	};
}

#endif
