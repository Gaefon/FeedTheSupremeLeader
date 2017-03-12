#include <Window.h>

using namespace std;

namespace GEngine
{
	Window::Window(string title, unsigned int width, unsigned int height)
	{
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
}
