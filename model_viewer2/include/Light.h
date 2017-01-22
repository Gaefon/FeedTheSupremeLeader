#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
	private:
		float m_intensity;
		glm::vec3 m_color;
		glm::vec3 m_position;
		glm::vec3 m_direction;
		
	public:
		Light();
		~Light();
		void setColor(glm::vec3 col);
		void setPosition(glm::vec3 pos);
		void setDirection(glm::vec3 dir);
		
};

#endif
