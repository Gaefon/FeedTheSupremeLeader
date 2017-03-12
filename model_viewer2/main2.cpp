#include <GEngine.h>
#include <Version.h>
#include <Window.h>
#include <Surface.h>
#include <Device.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <list>

using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	
	glfwInit();
	
	window = new Window("lol", 800, 600);
	
	Engine engine("test", Version::makeVersion(1, 0, 0));
	Surface surface(&engine, window);
	PhysicalDevice *phys_dev = surface.getSuitableDevice(&engine);
	engine.pickPhysicalDevices();
	Device dev(phys_dev);
	
	//X11Surface surface(&engine, glfwGetX11Display(), glfwGetX11Window(window));
	//XcbSurface surface(&engine, nullptr, 42);
	//WaylandSurface surface(&engine, info.info.wl.display, info.info.wl.surface);
	
	list<PhysicalDevice *> devs = engine.getListPhysicalDevices();
	for (list<PhysicalDevice *>::iterator i = devs.begin(); i != devs.end(); i++)
	{
		cout << (*i)->getDeviceName() << endl;
		cout << "0x" << hex << (*i)->getVendorId() << endl;
		cout << "0x" << hex << (*i)->getDeviceId() << endl;
		cout << Version::versionToString((*i)->getApiVersion()) << endl;
		cout << Version::versionToString((*i)->getDriverVersion()) << endl;
	}
	
	while (!window->shouldClose())
	{
		glfwPollEvents();
	}
	
	delete window;
	glfwTerminate();
	
	return 0;
}
