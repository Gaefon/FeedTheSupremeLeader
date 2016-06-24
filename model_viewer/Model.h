#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model
{
	private:
		std::vector<glm::vec3> vertices;
		void loadFile(std::string file_name);
	public:
		Model(std::string file_name);
		~Model();
};

#endif
