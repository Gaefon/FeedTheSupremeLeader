#ifndef COMMAND_BUFFERS_H
#define COMMAND_BUFFERS_H

#include <vector>
#include <vulkan/vulkan.h>
#include <Device.h>
#include <PhysicalDevice.h>
#include <buffers/Framebuffers.h>
#include <Pipeline.h>
#include <Semaphore.h>
#include <buffers/VertexBuffer.h>
#include <buffers/IndexBuffer.h>

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

			void beginCommandBufferAndRenderPass(RenderPass *render_pass, Framebuffers *framebuffers, SwapChain *sc);
			void startRecording(Pipeline *pipeline, VertexBuffer *vertex_buffer, IndexBuffer *index_buffer);
			void endCommandBufferAndRenderPass();
			void draw(SwapChain *sc);
	};
}

#endif
