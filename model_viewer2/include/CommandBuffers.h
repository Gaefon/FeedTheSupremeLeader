#ifndef COMMAND_BUFFERS_H
#define COMMAND_BUFFERS_H

#include <vector>

#include <vulkan/vulkan.h>

#include <Device.h>
#include <PhysicalDevice.h>
#include <Framebuffers.h>
#include <Pipeline.h>
#include <Semaphore.h>
#include <VertexBuffer.h>

namespace GEngine
{
	class CommandBuffers
	{
		private:
			VkCommandPool command_pool;
			std::vector<VkCommandBuffer> command_buffers;

			Semaphore img;
			Semaphore render;

			Device *device;

		public:
			CommandBuffers(Device *dev);
			~CommandBuffers();
            void copyBufferCommand(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
			void createCommandPool(PhysicalDevice *phys_dev);
			void createCommandBuffers(Framebuffers *frame_buffers);
			void startRecording(Framebuffers *framebuffers, SwapChain *sc, RenderPass *render_pass, Pipeline *pipeline, VertexBuffer *vertex_buffer);
			void draw(SwapChain *sc);
	};
}

#endif
