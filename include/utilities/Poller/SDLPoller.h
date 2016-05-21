#ifndef SDLPOLLER_H
#define SDLPOLLER_H

#include <utilities/Poller/EventPoller.h>


class SDLPoller : public EventPoller
{
	public:
		void Poll();
		SDLPoller();
		virtual ~SDLPoller();

	protected:

	private:
		void notify(SDL_Event event);
};

#endif // SDLPOLLER_H
