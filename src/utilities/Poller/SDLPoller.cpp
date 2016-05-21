#include <SDL.h>
#include <utilities/Poller/SDLPoller.h>

using namespace std;

SDLPoller::SDLPoller()
{
	//ctor
}

SDLPoller::~SDLPoller()
{
	//dtor
}

void SDLPoller::notify(SDL_Event event)
{
	(void) event;
	list<SdlObserver *> observers = getObservers();
	list<SdlObserver *>::iterator elt;
	for (elt = observers.begin(); elt != observers.end(); elt++)
	{
		(*elt)->onSdlEventReceived(event);
	}
}


void SDLPoller::Poll()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type != 0)
		{
			notify(event);
		}
	}
}
