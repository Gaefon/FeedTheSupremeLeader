#ifndef COMMAND_BUFFERS_H
#define COMMAND_BUFFERS_H

#include <vector>

#include <vulkan/vulkan.h>

#include <Device.h>
#include <PhysicalDevice.h>
#include <Framebuffers.h>

namespace GEngine
{
	class CommandBuffers
	{
		private:
			VkCommandPool command_pool;
			std::vector<VkCommandBuffer> command_buffers;
			
			Device *device;
		
		public:
			CommandBuffers();
			~CommandBuffers();
			
			void createCommandPool(Device *dev, PhysicalDevice *phys_dev);
			void createCommandBuffers(Framebuffers *frame_buffers);
			void startRecording(Framebuffers *framebuffers, SwapChain *sc, RenderPass *render_pass);
	};
}

#endif
