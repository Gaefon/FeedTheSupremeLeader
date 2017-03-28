#include <Framebuffers.h>

using namespace std;

namespace GEngine
{
	Framebuffers::Framebuffers()
	{
		logical_device = nullptr;
	}
	
	Framebuffers::~Framebuffers()
	{
		for (vector<VkFramebuffer>::iterator it = framebuffers.begin(); it != framebuffers.end(); it++)
		{
			 if (*it != VK_NULL_HANDLE && logical_device != nullptr)
			 {
			 	vkDestroyFramebuffer(logical_device->getVulkanObject(), *it, nullptr);
			 }
		}
	}
	
	void Framebuffers::createFramebuffer(Device *dev, SwapChain *swap_chain, RenderPass *render_pass)
	{
		framebuffers.resize(swap_chain->getImageViews().size(), VK_NULL_HANDLE);
		
		vector<ImageView *> list_img_views(swap_chain->getImageViews());
		
		for (unsigned int i = 0; i < list_img_views.size(); i++)
		{
			VkImageView attachments[] = { list_img_views[i]->getVulkanObject() };
			
			VkFramebufferCreateInfo framebuffer_infos = {};
			framebuffer_infos.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebuffer_infos.renderPass = render_pass->getVulkanObject();
			framebuffer_infos.attachmentCount = 1;
			framebuffer_infos.pAttachments = attachments;
			framebuffer_infos.width = swap_chain->getExtent().width;
			framebuffer_infos.height = swap_chain->getExtent().height;
			framebuffer_infos.layers = 1;
			
			if (vkCreateFramebuffer(dev->getVulkanObject(), &framebuffer_infos, nullptr, &framebuffers[i]) != VK_SUCCESS)
			{
				framebuffers[i] = VK_NULL_HANDLE;
				cerr << "failed to create framebuffer" << endl;
			}
		}
	}

}
