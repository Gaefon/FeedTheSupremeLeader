#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	
	SDL_Window *window;
	SDL_GLContext gl_context(0);
	bool finished = false;
	SDL_Event event;
	Camera camera;
	glm::vec3 cam_pos(-0.5f, -0.5f, 2.5f);
	glm::vec3 cam_target(2.0f, 2.0f, 0.0f);
	glm::vec3 cam_vert(0.0f, 0.0f, 1.0f);
	
	
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("lol", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	gl_context = SDL_GL_CreateContext(window);
	
	glewInit();
	
	camera.setPerspectice(90.0f, 800.0f / 600.0f, 1.0f, 100.0f);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	Shader shader_color("Shaders/3d_color.vert", "Shaders/3d_color.frag");
	shader_color.load();
	
	glEnable(GL_DEPTH_TEST);
	
	Model model(argv[1]);
	float vertices[] =
	{
		0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 3.0f, 0.0f, 0.0f,
		3.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 3.0f, 3.0f, 0.0f
	};
	
	float colors[] =
	{
		0.023f, 0.456f, 0.014f, 0.023f, 0.456f, 0.014f, 0.023f, 0.456f, 0.014f,
		0.023f, 0.456f, 0.014f, 0.023f, 0.456f, 0.014f, 0.023f, 0.456f, 0.014f
	};
	
	while(!finished)
	{
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				finished = true;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shader_color.getProgramID());
		
		camera.setLookAt(cam_pos, cam_target, cam_vert);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
		glEnableVertexAttribArray(1);
		
		
		glUniformMatrix4fv(glGetUniformLocation(shader_color.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(camera.getModelview()));
		glUniformMatrix4fv(glGetUniformLocation(shader_color.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(camera.getProjection()));
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		
		model.render(camera, shader_color);
		
		glUseProgram(0);
		SDL_GL_SwapWindow(window);
		SDL_Delay(20);
	}
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
