#include "Model.h"
#include <fstream>

using namespace std;

Model::Model(string file_name)
{
	loadFile(file_name);
}

Model::~Model()
{
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
			else if (type == "f")
			{
			}
		}
		fd.close();
	}
}
