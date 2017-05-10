#ifndef VERTEX_CLASS_H
#define VERTEX_CLASS_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace GEngine
{
	class Vertex
    {
    	private:
			glm::vec3 v_position;
			glm::vec3 v_color;
	
		public:
			Vertex(glm::vec3 pos, glm::vec3 color);
			~Vertex();
			
			glm::vec3 getPosition();
			glm::vec3 getColor();
    };
}
#endif
