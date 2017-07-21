#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include <models/Vertex.h>

#include <models/Material.h>

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
			std::vector<uint16_t> arr_indexes;
			Material *material;

			std::vector<std::string> splitStr(std::string data, std::string delimeter = " ");
			void loadFile(std::string file_name);
			int findVertexIndex(std::vector<int *> *vertex_indexes, int *vert);
		public:
			Model();
			Model(std::string file_name);
			~Model();
			void addVertice(Vertex *new_vertex);
			void addIndex(uint16_t new_index);
			std::vector<Vertex *> getVertices();
			std::vector<uint16_t> getIndexes();
			void setMaterial(Material *mat);
			Material *getMaterial();
			int getNbVertices();
	};
}

#endif
