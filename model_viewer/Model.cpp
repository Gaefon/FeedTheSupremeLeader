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
				int first_space = data.find(" ");
				string x = data.substr(0, first_space);
				int second_space = data.substr(first_space + 1).find(" ") + first_space + 1;
				string y = data.substr(first_space + 1, second_space - first_space - 1);
				string z = data.substr(second_space + 1);
				tmp_vert.push_back(glm::vec3(stof(x), stof(y), stof(z)));
			}
			else if (type == "f")
			{
			}
		}
		fd.close();
	}
}
