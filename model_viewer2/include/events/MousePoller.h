#ifndef MOUSE_POLLER_H
#define MOUSE_POLLER_H

#include <Window.h>
#include <events/MouseEvent.h>

#include <vector>

namespace GEngine
{
	class MousePoller
	{
		private:
			Window *window;
			
			std::vector<MouseEvent *> current_events;
			
			void clearEvents();

			class MouseEventPool
			{
				private:
					static MouseEventPool *m_instance;
					std::vector<MouseEvent *> available_commands;
				
				public:
					MouseEventPool();
					~MouseEventPool();
					
					static MouseEventPool *getInstance();
					MouseEvent *getAvailableEvent();
					void releaseEvent(MouseEvent *event);
			};
			
		public:
			MousePoller(Window *win);
			~MousePoller();
			
			void poll();
			std::vector<MouseEvent *> getEvents();
			void callbackPosition(GLFWwindow *win, double xpos, double ypos);
			void callbackMouseButton(GLFWwindow *win, int button, int action, int mods);
	};
}

#endif
