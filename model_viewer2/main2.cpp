
#include <GEngineWrapper.h>
#include <Window.h>
#include <string>
using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	list<string> extensions;

	glfwInit();

	window = new Window("Heroes never die !", 800, 600);

	GEngineWrapper g_engine_wrapper(window);

	while (!window->shouldClose())
	{
		glfwPollEvents();
		g_engine_wrapper.startDrawing();
	}
	
	g_engine_wrapper.getEngine()->getLogicalDevice()->waitIdle();

	delete window;
	glfwTerminate();

	return 0;
}
