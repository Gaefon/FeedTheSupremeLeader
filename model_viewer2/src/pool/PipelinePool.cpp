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
}
