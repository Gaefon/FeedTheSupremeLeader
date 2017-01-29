#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <helper/DebugHelper.h>

Shader *DebugHelper::m_shader = NULL;

void DebugHelper::initShader(Shader *shader)
{
	m_shader = shader;
}

void DebugHelper::drawAxis(float size, Camera *camera)
{
	static const GLfloat g_vertex_buffer_data[] =
	{
		0.0f, 0.0f ,0.0f,
		size, 0.0f ,0.0f,
		0.0f, 0.0f ,0.0f,
		0.0f, size ,0.0f,
		0.0f, 0.0f ,0.0f,
		0.0f, 0.0f ,size
	};
	static const GLfloat g_color_buffer_data[] =
	{
		1.0f, 0.0f ,0.0f,
		1.0f, 0.0f ,0.0f,
		0.0f, 1.0f ,0.0f,
		0.0f, 1.0f ,0.0f,
		0.0f, 0.0f ,1.0f,
		0.0f, 0.0f ,1.0f
	};
	
	
	static const GLfloat g_normal_buffer_data[] =
	{
		0.0f, 0.0f ,1.0f,
		0.0f, 0.0f ,1.0f,
		0.0f, 0.0f ,1.0f
	};
	
	glUseProgram(m_shader->getProgramID());
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, g_vertex_buffer_data);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, g_color_buffer_data);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, g_normal_buffer_data);
	glEnableVertexAttribArray(2);
	
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(camera->getModelview()));
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(camera->getProjection()));
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "normal"), 1, GL_FALSE, value_ptr(glm::mat4(1.0f)));


	/*glEnableVertexAttribArray(1);	
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);	
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);*/
	
	glDrawArrays(GL_LINES, 0, 6);

	glDisableVertexAttribArray(2);	
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
	glUseProgram(0);

}
