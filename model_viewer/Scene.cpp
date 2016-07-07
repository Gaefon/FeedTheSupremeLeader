#include "Scene.h"


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

void Scene::addModel(Model *model)
{
	m_list_model.push_back(model);
}

void Scene::render()
{
}
