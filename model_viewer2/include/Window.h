#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

namespace GEngine
{

	class Window
	{
		private:
			GLFWwindow *window;
			
			unsigned int width;
			unsigned int height;
			
		public:
			Window(std::string title, unsigned int width, unsigned int height);
			~Window();
			
			bool shouldClose();
			GLFWwindow *getGLFWObject();
			
			unsigned int getWidth();
			unsigned int getHeight();
	};
}

#endif