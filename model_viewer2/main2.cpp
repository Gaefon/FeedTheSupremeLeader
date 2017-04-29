#include <GEngineWrapper.h>
#include <Window.h>
#include <events/KeyboardPoller.h>
#include <events/MousePoller.h>

#include <string>

using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	KeyboardPoller *key_event;
	MousePoller *mouse_event;
	list<string> extensions;

	glfwInit();

	window = new Window("Heroes never die !", 800, 600);
	key_event = new KeyboardPoller(window);
	mouse_event = new MousePoller(window);

	GEngineWrapper g_engine_wrapper(window);

	while (!window->shouldClose())
	{
		key_event->poll();
		
		for (KeyEvent *evt: key_event->getEvents())
			cout << (int) evt->getKey() << " " << evt->isPressed() << endl;
			
		for (MouseEvent *evt : mouse_event->getEvents())
		{
			if (evt->getType() == MouseEvent::Type::position)
				cout << "X = " << evt->getPosX() << " // Y = " << evt->getPosY() << endl;
			else
				cout << "Button = " << (int) evt->getType() << " // pressed = " << evt->isPressed() << endl;
		}
		mouse_event->poll();
		
		g_engine_wrapper.startDrawing();
	}
	
	g_engine_wrapper.getEngine()->getLogicalDevice()->waitIdle();

	delete key_event;
	delete window;
	glfwTerminate();

	return 0;
}
