#include <SDL.h>
#include <utilities/Poller/VillagePoller.h>

using namespace std;

VillagePoller::VillagePoller()
{
}

VillagePoller::~VillagePoller()
{
}

void VillagePoller::notify(Village *village)
{
    list<VillageObserver *> observers = getObservers();
	list<VillageObserver *>::iterator elt;
	for (elt = observers.begin(); elt != observers.end(); elt++)
	{
		if ((*elt)->onVillageUpdateRequest(village))
			break;
	}
}
