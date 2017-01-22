#include <Scene.h>

using namespace std;


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::setCamera(Camera *cam)
{
	m_cam = cam;
}

void Scene::addLight(Light *light)
{
	m_list_light.push_back(light);
}

void Scene::addModel(Model *model)
{
	m_list_model.push_back(model);
}

void Scene::render()
{
	for (vector<Model *>::iterator it = m_list_model.begin(); it != m_list_model.end(); it++)
		(*it)->render(m_cam);
}
