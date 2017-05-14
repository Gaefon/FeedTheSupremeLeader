#include <models/Material.h>

namespace GEngine
{
	Material::Material(Pipeline *pipe)
	{
		pipeline = pipe;
	}
	
	Material::~Material()
	{
	}
	
	Pipeline *Material::getPipeline()
	{
		return pipeline;
	}
}
