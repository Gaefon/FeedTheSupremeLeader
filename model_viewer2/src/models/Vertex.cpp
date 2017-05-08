#include <models/Vertex.h>

using namespace std;

namespace GEngine
{
	Vertex::Vertex(glm::vec3 pos, glm::vec3 color)
	{
		v_position = pos;
		v_color = color;
	}
	
	Vertex::~Vertex()
	{
	}
	
	glm::vec3 Vertex::getPosition()
	{
		return v_position;
	}
	
	glm::vec3 Vertex::getColor()
	{
		return v_color;
	}
}
