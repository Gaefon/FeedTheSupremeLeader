#include <models/Model.h>

#include <models/Vertex.h>

#include <string.h>
#include <algorithm>

using namespace std;

namespace GEngine
{

	Model::Model()
	{
	}

	Model::Model(string file_name)
	{
		loadFile(file_name);
	}

	Model::~Model()
	{
		for (vector<Vertex *>::iterator tmp = arr_vertices.begin(); tmp != arr_vertices.end(); ++tmp)
			delete *tmp;
	}
	
	void Model::addVertice(Vertex *new_vertex)
	{
		arr_vertices.push_back(new_vertex);
	}
	
	void Model::addIndex(uint16_t new_index)
	{
		arr_indexes.push_back(new_index);
	}
	
	vector<Vertex *> Model::getVertices()
	{
		return arr_vertices;
	}
	
	std::vector<uint16_t> Model::getIndexes()
	{
		return arr_indexes;
	}
	
	void Model::setMaterial(Material *mat)
	{
		material = mat;
	}
	
	Material *Model::getMaterial()
	{
		return material;
	}
	
	int Model::getNbVertices()
	{
		return arr_vertices.size();
	}

	vector<string> Model::splitStr(string data, string delimiter)
	{
		vector<string> lst;

		int first_space = data.find(delimiter);
		lst.push_back(data.substr(0, first_space));
		int second_space = data.substr(first_space + 1).find(delimiter) + first_space + 1;
		lst.push_back(data.substr(first_space + 1, second_space - first_space - 1));
		lst.push_back(data.substr(second_space + 1));

		return lst;
	}
	
	bool bothAreSpaces(char lhs, char rhs)
	{
		return (lhs == rhs) && (lhs == ' ');
	}

	void Model::loadFile(string file_name)
	{
		ifstream fd;
		string line;
		string type;
		string data;
		std::vector<glm::vec3> tmp_vert;
		std::vector<glm::vec3> tmp_normals;
		std::vector<glm::vec2> tmp_uvs;
		std::vector<int *> arr_faces;
		//int num_face = 0;

		//srand(time(NULL));

		fd.open(file_name);
		if (fd.is_open())
		{
			while (getline(fd, line))
			{
				// remove all double spaces
				string::iterator new_end = unique(line.begin(), line.end(), bothAreSpaces);
				line.erase(new_end, line.end());
				
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
					int x = 0;
					int dat[3][3];
					for (vector<string>::iterator it = coords.begin(); it != coords.end(); it++)
					{
						int y = 0;
						vector<string> vertex = splitStr(*it, "/");
						for (vector<string>::iterator itr = vertex.begin(); itr != vertex.end(); itr++)
						{
							dat[x][y] = atoi((*itr).c_str());
							y++;
						}
						x++;
					}
					
					for (int i = 0; i < 3; i++)
					{
						int idx = findVertexIndex(&arr_faces, dat[i]);
						arr_indexes.push_back(idx);
					}
				}
			}
			fd.close();
			
			for (vector<int *>::iterator it = arr_faces.begin(); it != arr_faces.end(); it++)
			{
				int vert_idx = (*it)[0] - 1;
				int normal_idx = (*it)[2] - 1;
				int uv_idx = (*it)[1] - 1;
				Vertex *vert = new Vertex(tmp_vert.at(vert_idx), {1.0f, 1.0f, 1.0f}, tmp_normals.at(normal_idx), tmp_uvs.at(uv_idx));
				arr_vertices.push_back(vert);
			}
			
			// clear all the found indices
			for (vector<int *>::iterator it = arr_faces.begin(); it != arr_faces.end(); it++)
				delete[] (*it);
		}
	}
	
	int Model::findVertexIndex(vector<int *> *vertex_indexes, int *vert)
	{
		unsigned int index;
		
		for (index = 0; index < vertex_indexes->size(); index++)
		{
			if (vertex_indexes->at(index)[0] == vert[0] && vertex_indexes->at(index)[1] == vert[1] && vertex_indexes->at(index)[2] == vert[2])
				return index;
		}
		
		// add the vertex
		int *face;
		face = new int[3];
		memcpy(face, vert, 3 * sizeof(int));
		vertex_indexes->push_back(face);
		
		return vertex_indexes->size() - 1;
	}
}

