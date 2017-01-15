#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>

#include "Shader.h"

using namespace std;

Shader::Shader() : m_vertex_source(), m_fragment_source()
{
	m_vertex_id = 0;
	m_fragment_id = 0;
	m_program_id = 0;
}


Shader::Shader(Shader const &copy)
{
	m_vertex_source = copy.m_vertex_source;
	m_fragment_source = copy.m_fragment_source;
	load();
}


Shader::Shader(string vertex_src, string fragment_src) : m_vertex_source(vertex_src), m_fragment_source(fragment_src)
{
	m_vertex_id = 0;
	m_fragment_id = 0;
	m_program_id = 0;
}


Shader::~Shader()
{
	if (m_vertex_id != 0)
		glDeleteShader(m_vertex_id);
	if (m_fragment_id != 0)
		glDeleteShader(m_fragment_id);
	if (m_program_id != 0)
		glDeleteProgram(m_program_id);
}

Shader& Shader::operator=(Shader const &copy)
{
	m_vertex_source = copy.m_vertex_source;
	m_fragment_source = copy.m_fragment_source;

	load();
	
	return *this;
}


bool Shader::load()
{
	if(m_vertex_id != 0 && glIsShader(m_vertex_id) == GL_TRUE)
		glDeleteShader(m_vertex_id);

	if(m_fragment_id != 0 && glIsShader(m_fragment_id) == GL_TRUE)
		glDeleteShader(m_fragment_id);

	if(m_program_id != 0 && glIsProgram(m_program_id) == GL_TRUE)
		glDeleteProgram(m_program_id);

	if(!compileShader(m_vertex_id, GL_VERTEX_SHADER, m_vertex_source))
		return false;

	if(!compileShader(m_fragment_id, GL_FRAGMENT_SHADER, m_fragment_source))
		return false;

	m_program_id = glCreateProgram();
	

	glAttachShader(m_program_id, m_vertex_id);
	glAttachShader(m_program_id, m_fragment_id);

	glBindAttribLocation(m_program_id, 0, "in_vertex");
	glBindAttribLocation(m_program_id, 1, "in_color");
	glBindAttribLocation(m_program_id, 2, "in_normals");
	glBindAttribLocation(m_program_id, 3, "in_uv");

	glLinkProgram(m_program_id);

	GLint link_error(0);
	glGetProgramiv(m_program_id, GL_LINK_STATUS, &link_error);

	if(link_error != GL_TRUE)
	{
		GLint error_size(0);
		
		glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &error_size);
		char *error = new char[error_size + 1];
		glGetShaderInfoLog(m_program_id, error_size, &error_size, error);
		error[error_size] = '\0';
		cerr << error << endl;
		delete[] error;
		glDeleteProgram(m_program_id);

		return false;
	}
	return true;
}


bool Shader::compileShader(GLuint &shader, GLenum type, string const &source_file)
{
	string line;
	string source_code;
	
	shader = glCreateShader(type);

	if(shader == 0)
	{
		cerr << "Error, the type (" << type << ") doesn't exists" << endl;
		return false;
	}
	
	ifstream file(source_file.c_str());
	if(!file)
	{
		cerr << "Error : file not found (" << source_file << ")" << endl;
		glDeleteShader(shader);

		return false;
	}

	while(getline(file, line))
		source_code += line + '\n';
	file.close();


	const GLchar* str_source = source_code.c_str();
	glShaderSource(shader, 1, &str_source, 0);
	glCompileShader(shader);


	GLint compile_error(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_error);

	if(compile_error != GL_TRUE)
	{
		GLint error_size(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_size);

		char *error = new char[error_size + 1];
		glGetShaderInfoLog(shader, error_size, &error_size, error);
		error[error_size] = '\0';
		cerr << error << endl;
		delete[] error;
		glDeleteShader(shader);

		return false;
	}
	return true;
}

GLuint Shader::getProgramID() const
{
	return m_program_id;
}
