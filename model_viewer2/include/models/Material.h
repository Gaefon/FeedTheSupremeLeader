#ifndef MATERIAL_H
#define MATERIAL_H

#include <Pipeline.h>

namespace GEngine
{
	class Material
	{
		private:
			Pipeline *pipeline;
			
		public:
		 	Material(Pipeline *pipe);
		 	~Material();
		 	
		 	Pipeline *getPipeline();
	};
}

#endif
