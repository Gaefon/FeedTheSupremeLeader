#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include <models/Vertex.h>

#include <Shader.h>

#include <glm/glm.hpp>
/*#include <glm/gtc/type_ptr.hpp>*/


/*#include "Camera.h"
#include "Shader.h"
#include "Texture.h"*/

namespace GEngine
{
	class Model
	{
		private:
			std::vector<Vertex *> arr_vertices;
	
	
			/*std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec3> colors;
			std::vector<glm::vec2> uvs;
			glm::mat4 normal_matrix;
			float *arr_vertices;
			float *arr_normals;
			float *arr_colors;
			float *arr_uvs;*/
		
			/*Shader *m_shader;
			Texture *m_texture;
		
			std::vector<std::string> splitStr(std::string data, std::string delimeter = " ");
			void loadFile(std::string file_name);*/
		public:
			Model();
			//Model(std::string file_name);
			~Model();
			void addVertice(Vertex *new_vertex);
			
			std::vector<glm::vec3> getVertexBufferData(Shader *shader);
	};
}

#endif
