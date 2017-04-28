#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include <Window.h>

namespace GEngine
{
	class MousePoller
	{
		private:
			double pos_x;
			double pos_y;
			
			Window *window;
			
		public:
			MousePoller(Window *win);
			~MousePoller();
			
			void poll();
			
			void getCurrentCursorPos(double *x, double *y);
			double getX();
			double getY();
			
			void callbackPosition(GLFWwindow *win, double xpos, double ypos);
	};
}

#endif
