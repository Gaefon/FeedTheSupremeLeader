#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

#include <GLFW/glfw3.h>
#include <Window.h>
#include <events/KeyEvent.h>

#include <vector>

namespace GEngine
{
	class KeyboardEvent
	{
		private:
			Window *window;
			
			std::vector<KeyEvent *> current_events;
			
			void clearEvents();
			
		
		public:
			KeyboardEvent(Window *win);
			~KeyboardEvent();
			
			void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			void poll();
			void wait();
			void wait(float timeout);
			
			std::vector<KeyEvent *> getEvents();
	};
}

#endif
