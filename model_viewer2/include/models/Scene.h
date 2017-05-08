#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <models/Model.h>

namespace GEngine
{
	class Scene
	{
		private:
			//Camera *m_cam;
			std::vector<Model *> m_list_model;
			//std::vector<Light *> m_list_light;
	
		public:
			Scene();
			~Scene();
			//void setCamera(Camera *cam);
			void addModel(Model *model);
			//void addLight(Light *light);
			void render();
	};
}

#endif
