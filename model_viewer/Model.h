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
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> colors;
		glm::mat4 normal_matrix;
		float *arr_vertices;
		float *arr_normals;
		float *arr_colors;
		
		Shader *m_shader;
		
		std::vector<std::string> splitStr(std::string data, std::string delimeter = " ");
		void loadFile(std::string file_name);
	public:
		Model();
		Model(std::string file_name);
		~Model();
		void setShader(Shader *shader);
		void addVertice(glm::vec3 vert, glm::vec3 color, glm::vec3 normal);
		void createModel();
		void render(Camera *camera);
};

#endif
