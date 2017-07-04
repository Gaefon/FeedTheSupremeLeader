#include <models/Scene.h>
#include <helper/DebugHelper.h>
#include <VertexBufferData.h>

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
		// voir methode startRecording dans le wrapper
		for (vector<Model *>::iterator it = m_list_model.begin(); it != m_list_model.end(); it++)
		{
			int position = 0;
			vector<VertexBufferData> all_vertices((*it)->getVertices().size());
			
			vector<Vertex *> vertices = (*it)->getVertices();
			for (vector<Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
			{
				all_vertices.at(position).v_position = (*itr)->getPosition();
				all_vertices.at(position).v_color = (*itr)->getColor();
				position++;
			}
			
			wrapper->startRecording((*it)->getMaterial()->getPipeline(), all_vertices, (*it)->getIndexes());
		}
	}
}
