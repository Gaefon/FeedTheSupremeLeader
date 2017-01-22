#include <Light.h>


Light::Light()
{
}

Light::~Light()
{
}

void Light::setColor(glm::vec3 col)
{
	m_color = col;
}

void Light::setPosition(glm::vec3 pos)
{
	m_position = pos;
}

void Light::setDirection(glm::vec3 dir)
{
	m_direction = dir;
}
