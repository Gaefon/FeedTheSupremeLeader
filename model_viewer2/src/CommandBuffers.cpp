#include <CommandBuffers.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	CommandBuffers::CommandBuffers()
	{
		command_pool = VK_NULL_HANDLE;
		device = nullptr;
	}

	CommandBuffers::~CommandBuffers()
	{
		if (command_pool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(device->getVulkanObject(), command_pool, nullptr);
		}


	}

	void CommandBuffers::createCommandPool(Device *dev, PhysicalDevice *phys_dev)
	{
		VkCommandPoolCreateInfo pool_create_infos = {};
		pool_create_infos.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_create_infos.queueFamilyIndex = phys_dev->getGraphicIndex();
		pool_create_infos.flags = 0;

		device = dev;

		if (vkCreateCommandPool(device->getVulkanObject(), &pool_create_infos, nullptr, &command_pool) != VK_SUCCESS)
		{
			command_pool = VK_NULL_HANDLE;
			cerr << "Failed to create command pool" << endl;
		}
	}

	void CommandBuffers::createCommandBuffers(Framebuffers *frame_buffers)
	{
		command_buffers.resize(frame_buffers->getSize(), VK_NULL_HANDLE);


		VkCommandBufferAllocateInfo command_buffer_alloc_infos = {};
		command_buffer_alloc_infos.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		command_buffer_alloc_infos.commandPool = command_pool;
		command_buffer_alloc_infos.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		command_buffer_alloc_infos.commandBufferCount = command_buffers.size();


		if (vkAllocateCommandBuffers(device->getVulkanObject(), &command_buffer_alloc_infos, command_buffers.data()) != VK_SUCCESS)
		{
			cerr << "Error allocating command buffers" << endl;
		}
	}

	void CommandBuffers::startRecording(Framebuffers *framebuffers, SwapChain *sc, RenderPass *render_pass, Pipeline *pipeline)
	{
		for (unsigned int i = 0; i < command_buffers.size(); i++)
		{
			VkCommandBufferBeginInfo begin_info = {};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			begin_info.pInheritanceInfo = nullptr;

			vkBeginCommandBuffer(command_buffers[i], &begin_info);

			VkRenderPassBeginInfo render_pass_info = {};

			render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			render_pass_info.renderPass = render_pass->getVulkanObject();
			render_pass_info.framebuffer = framebuffers->getVulkanObject(i);
			render_pass_info.renderArea.offset = {0, 0};
			render_pass_info.renderArea.extent = sc->getExtent();

			VkClearValue clear_color = {0.0f, 0.0f, 0.0f, 0.0f};
			render_pass_info.clearValueCount = 1;
			render_pass_info.pClearValues = &clear_color;

			vkCmdBeginRenderPass(command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getVulkanObject());
			vkCmdDraw(command_buffers[i], 3, 1, 0, 0);
			vkCmdEndRenderPass(command_buffers[i]);
		}
	}
}
