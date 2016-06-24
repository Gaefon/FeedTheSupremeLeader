#ifndef SHADER_H
#define SHADER_H


#ifdef WIN32
	#include <GL/glew.h>
#elif __APPLE__
	#define GL3_PROTOTYPES 1
	#include <OpenGL/gl3.h>
#else
	#define GL3_1 PROTOTYPES
	#include <GL/gl.h>
#endif


#include <string>

class Shader
{
    public:

		Shader();
		Shader(Shader const &copy);
		Shader(std::string vertex_src, std::string fragment_src);
		~Shader();

		Shader& operator=(Shader const &copy);

		bool load();
		bool compileShader(GLuint &shader, GLenum type, std::string const &source_file);
		GLuint getProgramID() const;


    private:

		GLuint m_vertex_id;
		GLuint m_fragment_id;
		GLuint m_program_id;

		std::string m_vertex_source;
		std::string m_fragment_source;
};

#endif
