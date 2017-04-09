
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

    window = new Window("卐 HEIL MEI! 卐", 800, 600);

	GEngineWrapper g_engine_wrapper(window);

    while (!window->shouldClose())
    {
     glfwPollEvents();
     g_engine_wrapper.startDrawing();
    }
    g_engine_wrapper.getDevice().waitIdle();

    delete window;
    glfwTerminate();

	return 0;
}
