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
