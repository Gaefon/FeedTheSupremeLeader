#ifndef KEYBOARD_POLLER_H
#define KEYBOARD_POLLER_H

#include <GLFW/glfw3.h>
#include <Window.h>
#include <events/KeyEvent.h>

#include <vector>

namespace GEngine
{
	class KeyboardPoller
	{
		private:
			Window *window;
			
			std::vector<KeyEvent *> current_events;
			
			void clearEvents();
			
			class KeyEventPool
			{
				private:
					static KeyEventPool *m_instance;
					std::vector<KeyEvent *> available_commands;
				public:
					KeyEventPool();
					~KeyEventPool();
					
					static KeyEventPool *getInstance();
					KeyEvent *getAvailableEvent();
					void releaseEvent(KeyEvent *event);
			};
		
		public:
			KeyboardPoller(Window *win);
			~KeyboardPoller();
			
			void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			void poll();
			void wait();
			void wait(float timeout);
			
			std::vector<KeyEvent *> getEvents();
	};
}

#endif
