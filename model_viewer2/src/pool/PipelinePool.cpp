#include <pool/PipelinePool.h>

using namespace std;

namespace GEngine
{
	PipelinePool *PipelinePool::m_instance = nullptr;

	PipelinePool::PipelinePool()
	{
	}
	
	PipelinePool::~PipelinePool()
	{
	}
	
	PipelinePool *PipelinePool::getInstance()
	{
		if (m_instance == nullptr)
		 m_instance = new PipelinePool();
		return m_instance;
	}
	
	Pipeline *PipelinePool::createPipeline(int key, Shader *vertex, Shader *fragment, GEngineWrapper *wrapper)
	{
		
		Pipeline *pipeline = new Pipeline(wrapper->getEngine()->getLogicalDevice());
		
		pipeline->setVertexInput();
		pipeline->setInputAssembler();
		pipeline->setVertexShader(vertex);
		pipeline->setFragmentShader(fragment);

		pipeline->setViewPort(wrapper->getWindow()->getWidth(), wrapper->getWindow()->getHeight());
		pipeline->setScissor(wrapper->getSwapchain()->getExtent());
		pipeline->createViewportStateInfos();

		pipeline->setRasterizerInfos();
		pipeline->setMultisamplingInfos();
		pipeline->setColorBlendAttachment();
		pipeline->createDynamicStateInfos();
		pipeline->createPipelineLayout();
		pipeline->createPipeline(wrapper->getRenderPass());

		pipeline->initFramebuffers(wrapper->getSwapchain(), wrapper->getRenderPass());
		
		pipeline_map[key] = pipeline;
		
		return pipeline;
	}
	
	Pipeline *PipelinePool::getPipeline(int key)
	{
		map<int, Pipeline*>::iterator it = pipeline_map.find(key);
		if(it != pipeline_map.end())
			return it->second;
		return nullptr;
	}
	
	void PipelinePool::addPipeline(int key, Pipeline *pipeline)
	{
		pipeline_map[key] = pipeline;
	}
	
	void PipelinePool::destroyAllThePipelines()
	{
		for (map<int, Pipeline*>::iterator it = pipeline_map.begin(); it != pipeline_map.end(); it++)
		{
			delete it->second;
		}
	}
	
}
