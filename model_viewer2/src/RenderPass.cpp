#include <RenderPass.h>

#include <iostream>

using namespace std;

namespace GEngine
{
	RenderPass::RenderPass()
	{
		render_pass = VK_NULL_HANDLE;
		logical_device = nullptr;
	}
	
	RenderPass::~RenderPass()
	{
		if (render_pass != VK_NULL_HANDLE)
		{
			vkDestroyRenderPass(logical_device->getVulkanObject(), render_pass, nullptr);
		}
	}
	
	void RenderPass::initRenderPass(SwapChain *swap_chain, Device *dev)
	{
		logical_device = dev;
	
		VkAttachmentDescription color_attachment;
		color_attachment = {};
		color_attachment.format = swap_chain->getSurfaceFormat().format;
    	color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    	color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    	color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		
		
		VkAttachmentReference color_attachment_ref = {};
		color_attachment_ref.attachment = 0;
		color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		
		VkSubpassDescription sub_pass = {};
		sub_pass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		sub_pass.colorAttachmentCount = 1;
		sub_pass.pColorAttachments = &color_attachment_ref;
		
		VkRenderPassCreateInfo render_pass_info = {};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		render_pass_info.attachmentCount = 1;
		render_pass_info.pAttachments = &color_attachment;
		render_pass_info.subpassCount = 1;
		render_pass_info.pSubpasses = &sub_pass;
		
		if (vkCreateRenderPass(logical_device->getVulkanObject(), &render_pass_info, nullptr, &render_pass) != VK_SUCCESS)
		{
			render_pass = VK_NULL_HANDLE;
			cerr << "Error while creating render pass" << endl;
		}
	}
	
	VkRenderPass RenderPass::getVulkanObject()
	{
		return render_pass;
	}
}
