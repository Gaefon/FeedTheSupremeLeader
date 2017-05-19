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
		camera_shader.projection = glm::perspective(fovy, ratio, near, far);
	}

	void Camera::setLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 vert)
	{
		camera_shader.modelview = glm::lookAt(pos, target, vert);
	}
	
	Camera::CameraShaderObject *Camera::getShaderObject()
	{
		return &camera_shader;
	}
}
