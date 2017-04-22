#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include <Window.h>

namespace GEngine
{
	class MouseEvent
	{
		private:
			double pos_x;
			double pos_y;
			
			Window *window;
			
		public:
			MouseEvent(Window *win);
			~MouseEvent();
			
			void poll();
			
			void getCurrentCursorPos(double *x, double *y);
			double getX();
			double getY();
			
			void callbackPosition(GLFWwindow *win, double xpos, double ypos);
	};
}

#endif
