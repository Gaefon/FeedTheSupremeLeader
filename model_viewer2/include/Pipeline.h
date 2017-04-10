#ifndef PIPELINE_H
#define PIPELINE_H

#include <vulkan/vulkan.h>
#include <Vertex.h>
#include <Shader.h>
#include <Device.h>
#include <RenderPass.h>
#include <SwapChain.h>
#include <Framebuffers.h>

namespace GEngine
{
	class Pipeline
	{
		private:
			Shader *vertex_shader;
			Shader *fragment_shader;

			Device *logical_device;

			Framebuffers *framebuffers;

			VkPipelineShaderStageCreateInfo pipeline_stages[2];
			VkPipelineVertexInputStateCreateInfo vertex_input_info;
			VkPipelineInputAssemblyStateCreateInfo input_assembly;

			VkViewport viewport;

			VkRect2D scissor;

			VkPipelineViewportStateCreateInfo viewport_state_infos;
			VkPipelineRasterizationStateCreateInfo rasterizer_infos;
			VkPipelineMultisampleStateCreateInfo multisampling_infos;
			VkPipelineColorBlendAttachmentState color_blend_attachment;
			VkPipelineColorBlendStateCreateInfo color_blend_state;

			VkDynamicState dynamic_states[2];
			VkPipelineDynamicStateCreateInfo dynamic_state_infos;

			VkPipelineLayout pipeline_layout;
			VkGraphicsPipelineCreateInfo pipeline_info;

			VkPipeline pipeline;

			void cleanup();

		public:
			Pipeline(Device *dev);
			~Pipeline();

			void setVertexInput(Vertex *vertex);
			void setInputAssembler();
			void setVertexShader(Shader *new_shader);
			void setFragmentShader(Shader *new_shader);
			void setViewPort(float width, float height);
			void setScissor(VkExtent2D extent);
			void createViewportStateInfos();
			void setRasterizerInfos();
			void setMultisamplingInfos();
			void setColorBlendAttachment();
			void createDynamicStateInfos();
			void createPipelineLayout();
			void createPipeline(RenderPass *render_pass);

			bool initFramebuffers(SwapChain *swap_chain, RenderPass *render_pass);
			Framebuffers *getFramebuffers();

			VkPipeline getVulkanObject();
	};
}

#endif
