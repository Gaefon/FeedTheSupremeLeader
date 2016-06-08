#ifndef VILLAGE_POLLER_H
#define VILLAGE_POLLER_H

#include <utilities/Poller/EventPoller.h>
#include <utilities/Observer/VillageObserver.h>

class VillagePoller : public EventPoller<VillageObserver *>
{
	public:
		VillagePoller ();
		~VillagePoller ();
/*    private:
        void notify(Village *village);*/
};

#endif
