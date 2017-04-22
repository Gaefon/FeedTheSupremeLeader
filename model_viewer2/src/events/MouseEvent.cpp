#include <events/MouseEvent.h>

#include <map>

using namespace std;

namespace GEngine
{
	static map<GLFWwindow *, MouseEvent *> map_evt;
	
	static void cPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		map<GLFWwindow *, MouseEvent *>::iterator found = map_evt.find(window);
		
		if (found != map_evt.end())
			found->second->callbackPosition(window, xpos, ypos);
	}

	MouseEvent::MouseEvent(Window *win)
	{
		pos_x = -1;
		pos_y = -1;
		
		window = win;
		map_evt[win->getGLFWObject()] = this;
		glfwSetCursorPosCallback(window->getGLFWObject(), cPositionCallback);
	}
	
	MouseEvent::~MouseEvent()
	{
	}
	
	void MouseEvent::poll()
	{
	}
	
	void MouseEvent::getCurrentCursorPos(double *x, double *y)
	{
		glfwGetCursorPos(window->getGLFWObject(), x, y);
	}
	
	double MouseEvent::getX()
	{
		return pos_x;
	}
	
	double MouseEvent::getY()
	{
		return pos_y;
	}
	
	void MouseEvent::callbackPosition(GLFWwindow *win, double xpos, double ypos)
	{
		(void) win;
		pos_x = xpos;
		pos_y = ypos;
	}
}
