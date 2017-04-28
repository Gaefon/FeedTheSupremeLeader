#include <events/MousePoller.h>

#include <map>

using namespace std;

namespace GEngine
{
	static map<GLFWwindow *, MousePoller *> map_evt;
	
	static void cPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		map<GLFWwindow *, MousePoller *>::iterator found = map_evt.find(window);
		
		if (found != map_evt.end())
			found->second->callbackPosition(window, xpos, ypos);
	}

	MousePoller::MousePoller(Window *win)
	{
		pos_x = -1;
		pos_y = -1;
		
		window = win;
		map_evt[win->getGLFWObject()] = this;
		glfwSetCursorPosCallback(window->getGLFWObject(), cPositionCallback);
	}
	
	MousePoller::~MousePoller()
	{
	}
	
	void MousePoller::poll()
	{
	}
	
	void MousePoller::getCurrentCursorPos(double *x, double *y)
	{
		glfwGetCursorPos(window->getGLFWObject(), x, y);
	}
	
	double MousePoller::getX()
	{
		return pos_x;
	}
	
	double MousePoller::getY()
	{
		return pos_y;
	}
	
	void MousePoller::callbackPosition(GLFWwindow *win, double xpos, double ypos)
	{
		(void) win;
		pos_x = xpos;
		pos_y = ypos;
	}
}
