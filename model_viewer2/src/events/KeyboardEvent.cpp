#include <events/KeyboardEvent.h>

#include <helper/EventHelper.h>

#include <map>

using namespace std;

namespace GEngine
{
	static map<GLFWwindow *, KeyboardEvent *> map_evt;
	
	static void cKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		map<GLFWwindow *, KeyboardEvent *>::iterator found = map_evt.find(window);
		
		if (found != map_evt.end())
			found->second->keyCallback(window, key, scancode, action, mods);
	}
	
	
	KeyboardEvent::KeyboardEvent(Window *win)
	{
		window = win;
		map_evt[win->getGLFWObject()] = this;
		glfwSetKeyCallback(window->getGLFWObject(), cKeyCallback);
	}
	
	KeyboardEvent::~KeyboardEvent()
	{
		clearEvents();
	}
	
	void KeyboardEvent::clearEvents()
	{
		for (KeyEvent *evt: current_events)
			KeyboardEvent::KeyEventPool::getInstance()->releaseEvent(evt);
		current_events.clear();
	}
	
	void KeyboardEvent::poll()
	{
		clearEvents();
		glfwPollEvents();
	}
	
	void KeyboardEvent::wait()
	{
		clearEvents();
		glfwWaitEvents();
	}
	
	void KeyboardEvent::wait(float timeout)
	{
		clearEvents();
		glfwWaitEventsTimeout(timeout);
	}
	
	vector<KeyEvent *> KeyboardEvent::getEvents()
	{
		return current_events;
	}
	
	void KeyboardEvent::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
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
		
		KeyEvent *evt = KeyboardEvent::KeyEventPool::getInstance()->getAvailableEvent();
		evt->setKey(key_val, pressed, mod);
		current_events.push_back(evt);
	}
	
	
	
	
	
	
	KeyboardEvent::KeyEventPool *KeyboardEvent::KeyEventPool::m_instance = nullptr;
	
	KeyboardEvent::KeyEventPool::KeyEventPool()
	{
	}
	
	KeyboardEvent::KeyEventPool::~KeyEventPool()
	{
		for (KeyEvent *event: available_commands)
			delete event;
		available_commands.clear();
	}

	KeyboardEvent::KeyEventPool *KeyboardEvent::KeyEventPool::getInstance()
	{
		if (m_instance == nullptr)
			m_instance = new KeyEventPool();
		return m_instance;
	}
	
	KeyEvent *KeyboardEvent::KeyEventPool::getAvailableEvent()
	{
		if (!available_commands.empty())
		{
			KeyEvent *event = available_commands.at(available_commands.size() - 1);
			available_commands.pop_back();
			return event;
		}
		
		return new KeyEvent(KeyEvent::Key::unknown, false, 0);
	}
	
	void KeyboardEvent::KeyEventPool::releaseEvent(KeyEvent *event)
	{
		available_commands.push_back(event);
	}
}
