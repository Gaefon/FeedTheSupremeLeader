#include <Camera.h>
#include <glm/gtx/transform.hpp>

namespace GEngine
{
	Camera::Camera()
	{}

	Camera::~Camera()
	{}

	void Camera::setPerspective(float fovy, float ratio, float near, float far)
	{
		projection = glm::perspective(fovy, ratio, near, far);
		projection[1][1] *= -1;
	}

	void Camera::setLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 vert)
	{
		modelview = glm::lookAt(pos, target, vert);
	}
	
	glm::mat4 Camera::getModelView()
	{
		return modelview;
	}
	
	glm::mat4 Camera::getProjection()
	{
		return projection;
	}
}
