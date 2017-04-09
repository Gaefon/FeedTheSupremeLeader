#ifndef FRAMEBUFFERS_H
#define FRAMEBUFFERS_H

#include <vulkan/vulkan.h>

#include <Device.h>
#include <SwapChain.h>
#include <RenderPass.h>

#include <vector>

namespace GEngine
{
	class Framebuffers
	{
		private:
			std::vector<VkFramebuffer> framebuffers;
			
			Device *logical_device;
			
		public:
			Framebuffers();
			~Framebuffers();
			
			bool createFramebuffer(Device *dev, SwapChain *swap_chain, RenderPass *render_pass);
			unsigned int getSize();
			VkFramebuffer getVulkanObject(int i);
	};
}

#endif
