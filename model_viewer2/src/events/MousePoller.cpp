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
	
	static void cMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		map<GLFWwindow *, MousePoller *>::iterator found = map_evt.find(window);
		
		if (found != map_evt.end())
			found->second->callbackMouseButton(window, button, action, mods);
	}

	MousePoller::MousePoller(Window *win)
	{
		window = win;
		map_evt[win->getGLFWObject()] = this;
		glfwSetCursorPosCallback(window->getGLFWObject(), cPositionCallback);
		glfwSetMouseButtonCallback(window->getGLFWObject(), cMouseButtonCallback);
	}
	
	MousePoller::~MousePoller()
	{
		clearEvents();
	}
	
	void MousePoller::clearEvents()
	{
		for (MouseEvent *evt: current_events)
			MousePoller::MouseEventPool::getInstance()->releaseEvent(evt);
		current_events.clear();
	}
	
	void MousePoller::poll()
	{
		clearEvents();
	}
	
	vector<MouseEvent *> MousePoller::getEvents()
	{
		return current_events;
	}
	
	void MousePoller::callbackPosition(GLFWwindow *win, double xpos, double ypos)
	{
		(void) win;
		MouseEvent *event = MousePoller::MouseEventPool::getInstance()->getAvailableEvent();
		event->setType(MouseEvent::Type::position);
		event->setPos(xpos, ypos);
		current_events.push_back(event);
	}
	
	void MousePoller::callbackMouseButton(GLFWwindow *win, int button, int action, int mods)
	{
		(void) win;
		MouseEvent *event = MousePoller::MouseEventPool::getInstance()->getAvailableEvent();
		
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			event->setType(MouseEvent::Type::leftButton);
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			event->setType(MouseEvent::Type::rightButton);
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			event->setType(MouseEvent::Type::middleButton);
		
		if (action == GLFW_RELEASE)
			event->setPressed(false);
		else
			event->setPressed(true);
		
		current_events.push_back(event);
	}
	
	
	
	
	
	MousePoller::MouseEventPool *MousePoller::MouseEventPool::m_instance = nullptr;
	
	MousePoller::MouseEventPool::MouseEventPool()
	{
	}
	
	MousePoller::MouseEventPool::~MouseEventPool()
	{
		for (MouseEvent *event: available_commands)
			delete event;
		available_commands.clear();
	}

	MousePoller::MouseEventPool *MousePoller::MouseEventPool::getInstance()
	{
		if (m_instance == nullptr)
			m_instance = new MouseEventPool();
		return m_instance;
	}
	
	MouseEvent *MousePoller::MouseEventPool::getAvailableEvent()
	{
		if (!available_commands.empty())
		{
			MouseEvent *event = available_commands.at(available_commands.size() - 1);
			available_commands.pop_back();
			return event;
		}
		
		return new MouseEvent(MouseEvent::Type::unknown);
	}
	
	void MousePoller::MouseEventPool::releaseEvent(MouseEvent *event)
	{
		available_commands.push_back(event);
	}
}
