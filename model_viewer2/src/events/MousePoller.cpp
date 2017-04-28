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
		window = win;
		map_evt[win->getGLFWObject()] = this;
		glfwSetCursorPosCallback(window->getGLFWObject(), cPositionCallback);
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
