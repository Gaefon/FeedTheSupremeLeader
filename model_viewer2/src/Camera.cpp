#include <Camera.h>
#include <glm/gtx/transform.hpp>

namespace GEngine
{
	Camera::Camera()
	{}

	Camera::~Camera()
	{}

	void Camera::setPerspectice(float fovy, float ratio, float near, float far)
	{
		projection = glm::perspective(fovy, ratio, near, far);
	}

	void Camera::setLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 vert)
	{
		//modelview = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(2.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::lookAt(pos, target, vert);
	}

	glm::mat4 Camera::getModelview()
	{
		return modelview;
	}

	glm::mat4 Camera::getProjection()
	{
		return projection;
	}
}
