#ifndef SDLPOLLER_H
#define SDLPOLLER_H

#include <utilities/Poller/EventPoller.h>
#include <utilities/Observer/SdlObserver.h>


class SDLPoller : public EventPoller<SdlObserver *>
{
	public:
		SDLPoller();
		~SDLPoller();
		void Poll();

	protected:

	private:
		void notify(SDL_Event event);
};

#endif // SDLPOLLER_H
