#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Camera.h"
#include "Model.h"

class Scene
{
	private:
		Camera *m_cam;
		std::vector<Model *> m_list_model;
	
	public:
		Scene();
		~Scene();
		void setCamera(Camera *cam);
		void addModel(Model *model);
		void render();
};

#endif
