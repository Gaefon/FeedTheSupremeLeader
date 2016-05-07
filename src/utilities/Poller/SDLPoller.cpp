#include <utilities/Poller/Observer.h>
#include <utilities/Poller/EventPoller.h>
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

void SDLPoller::Poll()
{
    SDL_Event   event;
    while (SDL_PollEvent(&event))
    {
      if (event.type != 0)
      {
        notify();
      }
    }
}
