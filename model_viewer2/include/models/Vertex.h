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
			glm::vec3 v_normal;
			glm::vec2 v_uv;
	
		public:
			Vertex(glm::vec3 pos, glm::vec3 color);
			Vertex(glm::vec3 pos, glm::vec3 color, glm::vec3 normal);
			Vertex(glm::vec3 pos, glm::vec3 color, glm::vec3 normal, glm::vec2 uv);
			~Vertex();
			
			glm::vec3 getPosition();
			glm::vec3 getColor();
			glm::vec3 getNormal();
			glm::vec2 getUv();
    };
}
#endif
