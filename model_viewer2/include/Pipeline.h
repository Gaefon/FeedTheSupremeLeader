#ifndef PIPELINE_H
#define PIPELINE_H

#include <vulkan/vulkan.h>

#include <Shader.h>
#include <Device.h>
#include <RenderPass.h>

namespace GEngine
{
	class Pipeline
	{
		private:
			Shader *vertex_shader;
			Shader *fragment_shader;
			
			Device *logical_device;
			
			VkPipelineShaderStageCreateInfo[2] pipeline_infos;
			VkPipelineVertexInputStateCreateInfo vertex_input_info;
			VkPipelineInputAssemblyStateCreateInfo input_assembly;
			
			VkViewport viewport;
			
			VkRect2D scissor;
			
			VkPipelineViewportStateCreateInfo viewport_state_infos;
			VkPipelineRasterizationStateCreateInfo rasterizer_infos;
			VkPipelineMultisampleStateCreateInfo multisampling_infos;
			VkPipelineColorBlendAttachmentState color_blend_attachment;
			VkPipelineColorBlendStateCreateInfo color_blend_state;
			VkPipelineDynamicStateCreateInfo dynamic_state_infos;
			
			VkPipelineLayout pipeline_layout;
			VkGraphicsPipelineCreateInfo pipeline_info;
			
			VkPipeline pipeline;
			
			void cleanup();
		
		public:
			Pipeline();
			~Pipeline();
			
			void setVertexInput();
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
			void createPipelineLayout(Device *dev);
			void createPipeline(RenderPass *render_pass);
	};
}

#endif
