#ifndef PIPELINE_POOL_H
#define PIPELINE_POOL_H

#include <map>

#include <Pipeline.h>

namespace GEngine
{
	class PipelinePool
	{
		private:
			static PipelinePool *m_instance;
			
			std::map<int, Pipeline *> pipeline_map;
		
			PipelinePool();
			~PipelinePool();
		
		public:
			static PipelinePool *getInstance();
			Pipeline *getPipeline(int key);
			void addPipeline(int key, Pipeline *pipeline);
	};
}

#endif
