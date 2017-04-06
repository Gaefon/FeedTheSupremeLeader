#include <CommandBuffers.h>

#include <iostream>
#include <limits>

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
	
	
	
	void CommandBuffers::draw(SwapChain *sc, Semaphore *img, Semaphore *render)
	{
		unsigned int img_index;
		
		vkAcquireNextImageKHR(device->getVulkanObject(), sc->getVulkanObject(), numeric_limits<uint64_t>::max(), img->getVulkanObject(), VK_NULL_HANDLE, &img_index);
		
		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore wait_semaphores[] = { img->getVulkanObject() };
		VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
		submit_info.waitSemaphoreCount = 1;
		submit_info.pWaitSemaphores = wait_semaphores;
		submit_info.pWaitDstStageMask = wait_stages;

		submit_info.commandBufferCount = 1;
		submit_info.pCommandBuffers = &(command_buffers.at(img_index));

		VkSemaphore signal_semaphores[] = { render->getVulkanObject() };
		submit_info.signalSemaphoreCount = 1;
		submit_info.pSignalSemaphores = signal_semaphores;
		
		if (vkQueueSubmit(device->getGraphicQueue(), 1, &submit_info, VK_NULL_HANDLE) != VK_SUCCESS)
			cerr << "failed to submit draw command buffer!" << endl;
		
		VkPresentInfoKHR present_info = {};
        present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        present_info.waitSemaphoreCount = 1;
        present_info.pWaitSemaphores = signal_semaphores;

        VkSwapchainKHR swap_chains[] = { sc->getVulkanObject() };
        present_info.swapchainCount = 1;
        present_info.pSwapchains = swap_chains;

        present_info.pImageIndices = &img_index;

        vkQueuePresentKHR(device->getPresentQueue(), &present_info);
		
	}
}
