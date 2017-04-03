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
			RenderPass();
			~RenderPass();
			
			void initRenderPass(SwapChain *swap_chain, Device *dev);
			
			VkRenderPass getVulkanObject();
			
			void startRenderPass();
	};
}

#endif
