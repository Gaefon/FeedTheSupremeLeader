#include <GEngine.h>
#include <Version.h>

#include <SDL2/SDL.h>

#include <iostream>
#include <list>

using namespace GEngine;
using namespace std;

int main(void)
{
	SDL_Window *window;
	SDL_GLContext gl_context(0);
	bool finished = false;
	SDL_Event event;

	Engine engine("test", Version::makeVersion(1, 0, 0));
	
	SDL_Init(SDL_INIT_VIDEO);

	// antialiasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);


	window = SDL_CreateWindow("lol", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	gl_context = SDL_GL_CreateContext(window);
	
	list<PhysicalDevice *> devs = engine.getListPhysicalDevices();
	for (list<PhysicalDevice *>::iterator i = devs.begin(); i != devs.end(); i++)
	{
		cout << (*i)->getDeviceName() << endl;
		cout << "0x" << hex << (*i)->getVendorId() << endl;
		cout << "0x" << hex << (*i)->getDeviceId() << endl;
		cout << Version::versionToString((*i)->getApiVersion()) << endl;
		cout << Version::versionToString((*i)->getDriverVersion()) << endl;
	}
	
	while (!finished)
	{
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				finished = true;
		}
	
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
