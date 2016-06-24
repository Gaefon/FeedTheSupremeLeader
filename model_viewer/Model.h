#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include "Camera.h"
#include "Shader.h"

class Model
{
	private:
		std::vector<glm::vec3> vertices;
		float *arr_vertices;
		float *arr_colors;
		
		std::vector<std::string> splitStr(std::string data, std::string delimeter = " ");
		void loadFile(std::string file_name);
	public:
		Model(std::string file_name);
		~Model();
		void render(Camera camera, Shader shader);
};

#endif
