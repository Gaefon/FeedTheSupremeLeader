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
        virtual void notify()
};

#endif // SDLPOLLER_H
