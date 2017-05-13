#include <models/Scene.h>
#include <helper/DebugHelper.h>

using namespace std;

namespace GEngine
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	/*void Scene::setCamera(Camera *cam)
	{
		m_cam = cam;
	}*/

	/*void Scene::addLight(Light *light)
	{
		m_list_light.push_back(light);
	}*/

	void Scene::addModel(Model *model)
	{
		m_list_model.push_back(model);
	}

	void Scene::render(GEngineWrapper *wrapper)
	{
		unsigned int total_vertices = 0;
		vector<glm::vec3> all_vertices;
		for (vector<Model *>::iterator it = m_list_model.begin(); it != m_list_model.end(); it++)
		{
			total_vertices += (*it)->getNbVertices();
			(*it)->getVertexBufferData(); //ajouter le shader en argument
			// mettre un getter temporaire dans le  wrapper
		}
	
		/*DebugHelper::drawAxis(1.0f, m_cam);
		for (vector<Model *>::iterator it = m_list_model.begin(); it != m_list_model.end(); it++)
			(*it)->render(m_cam);*/
	}
}
