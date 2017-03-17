#include <Window.h>

using namespace std;

namespace GEngine
{
	Window::Window(string title, unsigned int w, unsigned int h)
	{
		width = w;
		height = h;
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}
	
	bool Window::shouldClose()
	{
		if (glfwWindowShouldClose(window))
			return true;
		return false;
	}
	
	GLFWwindow *Window::getGLFWObject()
	{
		return window;
	}
	
	unsigned int Window::getWidth()
	{
		return width;
	}
	
	unsigned int Window::getHeight()
	{
		return height;
	}
}
