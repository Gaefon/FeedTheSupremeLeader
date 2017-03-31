#include <Pipeline.h>

#include <iostream>

#include <string.h>

using namespace std;

namespace GEngine
{
	Pipeline::Pipeline()
	{
		
		
		logical_device = nullptr;
		pipeline_layout = VK_NULL_HANDLE;
		pipeline = VK_NULL_HANDLE;
	}
	
	Pipeline::~Pipeline()
	{
		cleanup();
	}
	
	void Pipeline::setVertexInput()
	{
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_info.vertexBindingDescriptionCount = 0;
		vertex_input_info.pVertexBindingDescriptions = nullptr;
		vertex_input_info.vertexAttributeDescriptionCount = 0;
		vertex_input_info.pVertexAttributeDescriptions = nullptr;
	}
	
	void Pipeline::setInputAssembler()
	{
		input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly.primitiveRestartEnable = VK_FALSE;
	}
	
	void Pipeline::setVertexShader(Shader *new_shader)
	{
		vertex_shader = new_shader;
		
		pipeline_stages[0] = {};
		pipeline_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pipeline_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		//pipeline_stages[0].module = vertex_shader->getVulkanObject();
		memcpy(&(pipeline_stages[0].module), vertex_shader->getVulkanObject(), sizeof(VkShaderModule));
		pipeline_stages[0].pName = "main";
	}
	
	void Pipeline::setFragmentShader(Shader *new_shader)
	{
		fragment_shader = new_shader;
		
		pipeline_stages[1] = {};
		pipeline_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pipeline_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		//pipeline_stages[1].module = fragment_shader->getVulkanObject();
		memcpy(&(pipeline_stages[1].module), fragment_shader->getVulkanObject(), sizeof(VkShaderModule));
		pipeline_stages[1].pName = "main"; // faire une methode getName dans la class Shader
	}
	
	void Pipeline::setViewPort(float width, float height)
	{
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = width;
		viewport.height = height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
	}
	
	void Pipeline::setScissor(VkExtent2D extent)
	{
		scissor.offset = {0, 0};
		scissor.extent = extent;
		
		/*scissor.offset.x = 0;
		scissor.offset.y = 0;
		scissor.extent.width = extent.width;
		scissor.extent.height  = extent.height;*/
	}
	
	void Pipeline::createViewportStateInfos()
	{
		viewport_state_infos.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state_infos.viewportCount = 1;
		viewport_state_infos.pViewports = &viewport;
		viewport_state_infos.scissorCount = 1;
		viewport_state_infos.pScissors = &scissor;
	}
	
	void Pipeline::setRasterizerInfos()
	{
		rasterizer_infos.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer_infos.depthClampEnable = VK_FALSE;
		rasterizer_infos.rasterizerDiscardEnable = VK_FALSE;
		rasterizer_infos.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer_infos.lineWidth = 1.0f;
		rasterizer_infos.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer_infos.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer_infos.depthBiasEnable = VK_FALSE;
		rasterizer_infos.depthBiasConstantFactor = 0.0f;
		rasterizer_infos.depthBiasClamp = 0.0f;
		rasterizer_infos.depthBiasSlopeFactor = 0.0f;
	}
	
	void Pipeline::setMultisamplingInfos()
	{
		multisampling_infos.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling_infos.sampleShadingEnable = VK_FALSE;
		multisampling_infos.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling_infos.minSampleShading = 1.0f;
		multisampling_infos.pSampleMask = nullptr;
		multisampling_infos.alphaToCoverageEnable = VK_FALSE;
		multisampling_infos.alphaToOneEnable = VK_FALSE;
	}
	
	void Pipeline::setColorBlendAttachment()
	{
		color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		color_blend_attachment.blendEnable = VK_FALSE;
		color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
		color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
		
		color_blend_state.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		color_blend_state.logicOpEnable = VK_FALSE;
		color_blend_state.logicOp = VK_LOGIC_OP_COPY;
		color_blend_state.attachmentCount = 1;
		color_blend_state.pAttachments = &color_blend_attachment;
		color_blend_state.blendConstants[0] = 0.0f;
		color_blend_state.blendConstants[1] = 0.0f;
		color_blend_state.blendConstants[2] = 0.0f;
		color_blend_state.blendConstants[3] = 0.0f;
	}
	
	void Pipeline::createDynamicStateInfos()
	{
		dynamic_states[0] = VK_DYNAMIC_STATE_VIEWPORT;
		dynamic_states[1] = VK_DYNAMIC_STATE_LINE_WIDTH;
	
		dynamic_state_infos.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state_infos.dynamicStateCount = 2;
		dynamic_state_infos.pDynamicStates = dynamic_states;
	}
	
	void Pipeline::createPipelineLayout(Device *dev)
	{
		VkPipelineLayoutCreateInfo pipeline_layout_info = {};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 0;
		pipeline_layout_info.pSetLayouts = nullptr;
		pipeline_layout_info.pushConstantRangeCount = 0;
		pipeline_layout_info.pPushConstantRanges = 0;
		
		logical_device = dev;
		
		if (vkCreatePipelineLayout(logical_device->getVulkanObject(), &pipeline_layout_info, nullptr, &pipeline_layout) != VK_SUCCESS)
		{
			pipeline_layout = VK_NULL_HANDLE;
			logical_device = nullptr;
			cerr << "Error while creating pipeline layout" << endl;
		}
	}
	
	void Pipeline::createPipeline(RenderPass *render_pass)
	{
		pipeline_info = {};
		pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_info.stageCount = 2;
		pipeline_info.pStages = pipeline_stages;
		pipeline_info.pVertexInputState = &vertex_input_info;
		pipeline_info.pInputAssemblyState = &input_assembly;
		pipeline_info.pViewportState = &viewport_state_infos;
		pipeline_info.pRasterizationState = &rasterizer_infos;
		pipeline_info.pMultisampleState = &multisampling_infos;
		//pipeline_info.pDepthStencilState = nullptr;
		pipeline_info.pColorBlendState = &color_blend_state;
		//pipeline_info.pDynamicState = nullptr;
		
		pipeline_info.layout = pipeline_layout;
		
		pipeline_info.renderPass = render_pass->getVulkanObject();
		pipeline_info.subpass = 0;
		
		pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
		//pipeline_info.basePipelineIndex = -1;
		
		// erreur de segmentation je sais pas pourquoi, trop fatigué
		int ret = vkCreateGraphicsPipelines(logical_device->getVulkanObject(), VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline);
		if (logical_device == nullptr || ret != VK_SUCCESS)
		{
			cerr << "error creating pipeline" << endl;
			cerr << "error : " << ret << endl;
			pipeline = VK_NULL_HANDLE;
			logical_device = nullptr;
		}
	}
	
	void Pipeline::cleanup()
	{
		if (pipeline_layout != VK_NULL_HANDLE && logical_device != nullptr)
		{
			vkDestroyPipelineLayout(logical_device->getVulkanObject(), pipeline_layout, nullptr);
		}
		
		if (pipeline != VK_NULL_HANDLE && logical_device != nullptr)
		{
			vkDestroyPipeline(logical_device->getVulkanObject(), pipeline, nullptr);
		}
	}
}
