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
#include "Texture.h"

class Model
{
	private:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> colors;
		std::vector<glm::vec2> uvs;
		glm::mat4 normal_matrix;
		float *arr_vertices;
		float *arr_normals;
		float *arr_colors;
		float *arr_uvs;

		Shader *m_shader;
		Texture *m_texture;

		std::vector<std::string> splitStr(std::string data, std::string delimeter = " ");
		void loadFile(std::string file_name);
	public:
		Model();
		Model(std::string file_name);
		~Model();
		void setShader(Shader *shader);
		void setTexture(Texture *tex);
		void addVertice(glm::vec3 vert, glm::vec3 color, glm::vec3 normal);
		void addVertice(glm::vec3 vert, glm::vec3 color, glm::vec3 normal, glm::vec2 uv);
		void createModel();
		void render(Camera *camera);
};

#endif
