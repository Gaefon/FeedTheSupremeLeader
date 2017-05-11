#include <models/Model.h>

#include <models/Vertex.h>

#include <string.h>

using namespace std;

namespace GEngine
{

	Model::Model()
	{
	}

	/*Model::Model(string file_name)
	{
		arr_uvs = NULL;
		m_shader = NULL;
		normal_matrix = glm::mat4(1.0f);//(glm::vec3(1.0f), 1.0f);
		loadFile(file_name);
	}*/

	Model::~Model()
	{
		for (vector<Vertex *>::iterator tmp = arr_vertices.begin(); tmp != arr_vertices.end(); ++tmp)
			delete *tmp;
	}
	
	void Model::addVertice(Vertex *new_vertex)
	{
		arr_vertices.push_back(new_vertex);
	}
	
	int Model::getNbVertices()
	{
		return arr_vertices.size();
	}
	
	vector<glm::vec3> Model::getVertexBufferData(Shader *shader)
	{
		vector<glm::vec3> data;
		map<int, Shader::ArgumentType> *args = shader->getArgumentPosition();
		
		/*for (map<int, Shader::ArgumentType>::iterator it = args->begin(); it != args->end(); ++it)
		{
			if (it->second == Shader::ArgumentType::Vertex)
				size += arr_vertices.size() * Vertex::getPositionSize();
			else if (it->second == Shader::ArgumentType::Color)
				size += arr_vertices.size() * Vertex::getColorSize();
		}*/
		
		/*data = new float[size];
		int current_index = 0;*/
		
		for (vector<Vertex *>::iterator v_it = arr_vertices.begin(); v_it != arr_vertices.end(); ++v_it)
		{
			Vertex *vert = *v_it;
			
			for (map<int, Shader::ArgumentType>::iterator it = args->begin(); it != args->end(); ++it)
			{
				if (it->second == Shader::ArgumentType::Vertex)
					data.push_back(vert->getPosition());
				else if (it->second == Shader::ArgumentType::Color)
					data.push_back(vert->getColor());
			}
		}
		
		return data;
	}

	/*vector<string> Model::splitStr(string data, string delimiter)
	{
		vector<string> lst;

		int first_space = data.find(delimiter);
		lst.push_back(data.substr(0, first_space));
		int second_space = data.substr(first_space + 1).find(delimiter) + first_space + 1;
		lst.push_back(data.substr(first_space + 1, second_space - first_space - 1));
		lst.push_back(data.substr(second_space + 1));

		return lst;
	}

	void Model::loadFile(string file_name)
	{
		ifstream fd;
		string line;
		string type;
		string data;
		std::vector<glm::vec3> tmp_vert;
		std::vector<glm::vec3> tmp_colors;
		std::vector<glm::vec3> tmp_normals;
		std::vector<glm::vec2> tmp_uvs;

		srand(time(NULL));

		fd.open(file_name);
		if (fd.is_open())
		{
			while (getline(fd, line))
			{
				type = line.substr(0, line.find(" "));
				data = line.substr(line.find(" ") + 1);
				if (type == "v")
				{
					vector<string> coords = splitStr(data);
					tmp_vert.push_back(glm::vec3(atof(coords.at(0).c_str()), atof(coords.at(1).c_str()), atof(coords.at(2).c_str())));
				}
				else if (type == "vn")
				{
					vector<string> coords = splitStr(data);
					tmp_normals.push_back(glm::vec3(atof(coords.at(0).c_str()), atof(coords.at(1).c_str()), atof(coords.at(2).c_str())));
				}
				else if (type == "vt")
				{
					vector<string> coords = splitStr(data);
					tmp_uvs.push_back(glm::vec2(atof(coords.at(0).c_str()), atof(coords.at(1).c_str())));
				}
				else if (type == "f")
				{
					vector<string> coords = splitStr(data);
					for (vector<string>::iterator it = coords.begin(); it != coords.end(); it++)
					{
						vector<string> vertex = splitStr(*it, "/");
						if (tmp_uvs.size() > 0)
							addVertice(tmp_vert.at(atoi(vertex.at(0).c_str()) - 1), glm::vec3(1.0f, 1.0f, 1.0f), tmp_normals.at(atoi(vertex.at(2).c_str()) - 1), tmp_uvs.at(atoi(vertex.at(1).c_str()) - 1));
						else
							addVertice(tmp_vert.at(atoi(vertex.at(0).c_str()) - 1), glm::vec3(1.0f, 1.0f, 1.0f), tmp_normals.at(atoi(vertex.at(2).c_str()) - 1));
					}
				}
			}
			fd.close();

			createModel();
		}
	}*/
}

