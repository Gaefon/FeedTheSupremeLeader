#ifndef LIGHT_H
#define LIGHT_H

class Light
{
	private:
		float m_intensity;
		glm::vec3 m_color;
		glm::vec3 m_position;
		glm::vec3 m_direction;
		
	public;
		Light();
		~Light();
		setColor(glm::vec3 col);
		setPosition(glm::vec3 pos);
		setDirection(glm::vec3 dir);
		
};

#endif
