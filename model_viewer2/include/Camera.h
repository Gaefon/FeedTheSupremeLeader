#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

namespace GEngine
{
	class Camera
	{
		private:
			glm::mat4 modelview;
			glm::mat4 projection;
			
		public:
			Camera();
			~Camera();
			void setPerspective(float fovy, float ratio, float near, float far);
			void setLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 vert);
			glm::mat4 getModelView();
			glm::mat4 getProjection();
	};
}

#endif
