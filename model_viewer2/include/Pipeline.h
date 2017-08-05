#ifndef PIPELINE_H
#define PIPELINE_H

#include <vulkan/vulkan.h>
#include <Shader.h>
#include <Device.h>
#include <RenderPass.h>
#include <SwapChain.h>
#include <buffers/Framebuffers.h>
#include <buffers/VertexBuffer.h>
#include <buffers/StagingBuffer.h>
#include <buffers/IndexBuffer.h>
#include <buffers/UniformBuffer.h>
#include <DescriptorPool.h>
#include <DescriptorSet.h>

namespace GEngine
{
	class Pipeline
	{
		private:
			enum class ArgumentType : int
			{
				None = -1,
				Vertex = 0,
				Color = 1
			};

			Shader *vertex_shader;
			Shader *fragment_shader;

			Device *logical_device;
			
			StagingBuffer g_staging_buffer;
			StagingBuffer g_staging_buffer2;
			VertexBuffer g_vertex_buffer;
			IndexBuffer g_index_buffer;
			UniformBuffer g_uniform_buffer;
			
			DescriptorPool m_descriptor_pool;
			DescriptorSet m_descriptor_set;

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

			VkDescriptorSetLayout descriptor_set_layout;
			VkPipelineLayout pipeline_layout;
			VkGraphicsPipelineCreateInfo pipeline_info;

			VkPipeline pipeline;

			std::map<int, ArgumentType> argument_position;

			void cleanup();

		public:
			Pipeline(Device *dev);
			Pipeline(Device *dev, VkDescriptorSetLayout descriptorSet);
			~Pipeline();

			void createBuffers();
			void setVertexInput();
			void setInputAssembler();
			void setVertexShader(Shader *new_shader);
			Shader *getVertexShader();
			void setFragmentShader(Shader *new_shader);
			void setViewPort(float width, float height);
			void setScissor(VkExtent2D extent);
			void createViewportStateInfos();
			void setRasterizerInfos();
			void setMultisamplingInfos();
			void setColorBlendAttachment();
			void createDynamicStateInfos();
			void createUniformBuffer();
			void createPipelineLayout();
			void createPipeline(RenderPass *render_pass);

			VkPipeline getVulkanObject();

			void addArgumentType(int position, ArgumentType type);
			
			std::map<int, ArgumentType> *getArgumentPosition();
			
			void setVerticesAndIndexes(std::vector<VertexBufferData> vertices, std::vector<uint16_t> indexes);
			void updateDescriptorSet();
			
			VertexBuffer *getVertexBuffer();
			IndexBuffer *getIndexBuffer();
			StagingBuffer *getVertexStagingBuffer();
			StagingBuffer *getIndexStagingBuffer();
			UniformBuffer *getUniformBuffer();
			DescriptorSet *getDescriptorSet();
			VkPipelineLayout *getPipelineLayout();
	};
}

#endif
