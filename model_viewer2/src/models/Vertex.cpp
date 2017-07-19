#include <models/Vertex.h>

using namespace std;

namespace GEngine
{
	Vertex::Vertex(glm::vec3 pos, glm::vec3 color) : Vertex(pos, color, {0.0f, 0.0f, 0.0f})
	{}

	Vertex::Vertex(glm::vec3 pos, glm::vec3 color, glm::vec3 normal) : Vertex(pos, color, normal, {0.0f, 0.0f})
	{}
	
	Vertex::Vertex(glm::vec3 pos, glm::vec3 color, glm::vec3 normal, glm::vec2 uv)
	{
		v_position = pos;
		v_color = color;
		v_normal = normal;
		v_uv = uv;
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
	
	glm::vec3 Vertex::getNormal()
	{
		return v_normal;
	}
	
	glm::vec2 Vertex::getUv()
	{
		return v_uv;
	}
}
