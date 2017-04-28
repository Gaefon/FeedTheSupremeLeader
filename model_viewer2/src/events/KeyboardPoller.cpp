#include <events/KeyboardPoller.h>

#include <helper/EventHelper.h>

#include <map>

using namespace std;

namespace GEngine
{
	static map<GLFWwindow *, KeyboardPoller *> map_evt;
	
	static void cKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		map<GLFWwindow *, KeyboardPoller *>::iterator found = map_evt.find(window);
		
		if (found != map_evt.end())
			found->second->keyCallback(window, key, scancode, action, mods);
	}
	
	
	KeyboardPoller::KeyboardPoller(Window *win)
	{
		window = win;
		map_evt[win->getGLFWObject()] = this;
		glfwSetKeyCallback(window->getGLFWObject(), cKeyCallback);
	}
	
	KeyboardPoller::~KeyboardPoller()
	{
		clearEvents();
	}
	
	void KeyboardPoller::clearEvents()
	{
		for (KeyEvent *evt: current_events)
			KeyboardPoller::KeyEventPool::getInstance()->releaseEvent(evt);
		current_events.clear();
	}
	
	void KeyboardPoller::poll()
	{
		clearEvents();
		glfwPollEvents();
	}
	
	void KeyboardPoller::wait()
	{
		clearEvents();
		glfwWaitEvents();
	}
	
	void KeyboardPoller::wait(float timeout)
	{
		clearEvents();
		glfwWaitEventsTimeout(timeout);
	}
	
	vector<KeyEvent *> KeyboardPoller::getEvents()
	{
		return current_events;
	}
	
	void KeyboardPoller::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		(void) window;
		(void) scancode;
		
		bool pressed = true;
		int mod = 0;
		KeyEvent::Key key_val;
		
		if (action == GLFW_RELEASE)
			pressed = false;
		
		key_val = EventHelper::keyFromInt(key);
		mod = EventHelper::modFromInt(mods);
		
		KeyEvent *evt = KeyboardPoller::KeyEventPool::getInstance()->getAvailableEvent();
		evt->setKey(key_val, pressed, mod);
		current_events.push_back(evt);
	}
	
	
	
	
	
	
	KeyboardPoller::KeyEventPool *KeyboardPoller::KeyEventPool::m_instance = nullptr;
	
	KeyboardPoller::KeyEventPool::KeyEventPool()
	{
	}
	
	KeyboardPoller::KeyEventPool::~KeyEventPool()
	{
		for (KeyEvent *event: available_commands)
			delete event;
		available_commands.clear();
	}

	KeyboardPoller::KeyEventPool *KeyboardPoller::KeyEventPool::getInstance()
	{
		if (m_instance == nullptr)
			m_instance = new KeyEventPool();
		return m_instance;
	}
	
	KeyEvent *KeyboardPoller::KeyEventPool::getAvailableEvent()
	{
		if (!available_commands.empty())
		{
			KeyEvent *event = available_commands.at(available_commands.size() - 1);
			available_commands.pop_back();
			return event;
		}
		
		return new KeyEvent(KeyEvent::Key::unknown, false, 0);
	}
	
	void KeyboardPoller::KeyEventPool::releaseEvent(KeyEvent *event)
	{
		available_commands.push_back(event);
	}
}
