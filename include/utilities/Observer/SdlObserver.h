#ifndef SDL_OBSERVER_H
#define SDL_OBSERVER_H

#include <SDL.h>

class SdlObserver
{
	public:
		SdlObserver() {}
		~SdlObserver() {}
		virtual void onSdlEventReceived(SDL_Event event) = 0;
};

#endif