#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

namespace GEngine
{
	class Camera
	{
		public:
			typedef struct s_cameraShaderObject
			{
				glm::mat4 modelview;
				glm::mat4 projection;
			} CameraShaderObject;
		
		private:
			int pos;
			CameraShaderObject camera_shader;
		public:
			Camera();
			~Camera();
			void setPerspectice(float fovy, float ratio, float near, float far);
			void setLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 vert);
			CameraShaderObject *getShaderObject();
			
	};
}

#endif
