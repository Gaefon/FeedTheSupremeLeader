#include "Model.h"
#include <fstream>

#include <stdlib.h>
#include <time.h>

using namespace std;

Model::Model()
{
	m_shader = NULL;
	normal_matrix = glm::mat4(1.0f);//(glm::vec3(1.0f), 1.0f);
}

Model::Model(string file_name)
{
	loadFile(file_name);
	m_shader = NULL;
	normal_matrix = glm::mat4(1.0f);//(glm::vec3(1.0f), 1.0f);
}

Model::~Model()
{
	delete arr_vertices;
	delete arr_normals;
	delete arr_colors;
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

void Model::loadFile(string file_name)
{
	ifstream fd;
	string line;
	string type;
	string data;
	std::vector<glm::vec3> tmp_vert;
	std::vector<glm::vec3> tmp_colors;
	std::vector<glm::vec3> tmp_normals;
	
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
				tmp_vert.push_back(glm::vec3(stof(coords.at(0)), stof(coords.at(1)), stof(coords.at(2))));
			}
			else if (type == "vn")
			{
				vector<string> coords = splitStr(data);
				tmp_normals.push_back(glm::vec3(stof(coords.at(0)), stof(coords.at(1)), stof(coords.at(2))));
			}
			else if (type == "f")
			{				
				float r = 1.0f;
				float g = 1.0f;
				float b = 1.0f;
				vector<string> coords = splitStr(data);
				for (vector<string>::iterator it = coords.begin(); it != coords.end(); it++)
				{
					vector<string> vertex = splitStr(*it, "/");
					addVertice(tmp_vert.at(stoi(vertex.at(0)) - 1), glm::vec3(r, g, b), tmp_normals.at(stoi(vertex.at(2)) - 1));
				}
			}
		}
		fd.close();
		
		createModel();
	}
}

void Model::addVertice(glm::vec3 vert, glm::vec3 color, glm::vec3 normal)
{
	vertices.push_back(vert);
	colors.push_back(color);
	normals.push_back(normal);
}

void Model::createModel()
{
	arr_vertices = new float[vertices.size() * 3];
	arr_normals =  new float[normals.size() * 3];
	arr_colors =  new float[colors.size() * 3];
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		arr_vertices[i * 3] = vertices[i].x;
		arr_vertices[i * 3 + 1] = vertices[i].y;
		arr_vertices[i * 3 + 2] = vertices[i].z;
	
		arr_normals[i * 3] = normals[i].x;
		arr_normals[i * 3 + 1] = normals[i].y;
		arr_normals[i * 3 + 2] = normals[i].z;
	
		arr_colors[i * 3] = colors[i].x;
		arr_colors[i * 3 + 1] = colors[i].y;
		arr_colors[i * 3 + 2] = colors[i].z;
	}
}

void Model::setShader(Shader *shader)
{
	m_shader = shader;
}

void Model::render(Camera *camera)
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, arr_vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, arr_colors);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, arr_normals);
	glEnableVertexAttribArray(2);
	
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(camera->getModelview()));
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(camera->getProjection()));
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "normal"), 1, GL_FALSE, value_ptr(normal_matrix));
	
	
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

