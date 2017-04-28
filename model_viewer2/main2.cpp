#include <GEngineWrapper.h>
#include <Window.h>
#include <events/KeyboardPoller.h>

#include <string>
using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	KeyboardPoller *key_event;
	list<string> extensions;

	glfwInit();

	window = new Window("Heroes never die !", 800, 600);
	key_event = new KeyboardPoller(window);

	GEngineWrapper g_engine_wrapper(window);

	while (!window->shouldClose())
	{
		key_event->poll();
		for (KeyEvent *evt: key_event->getEvents())
			cout << (int) evt->getKey() << " " << evt->isPressed() << endl;
		g_engine_wrapper.startDrawing();
	}
	
	g_engine_wrapper.getEngine()->getLogicalDevice()->waitIdle();

	delete key_event;
	delete window;
	glfwTerminate();

	return 0;
}
