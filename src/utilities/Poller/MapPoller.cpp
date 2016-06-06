#include <SDL.h>
#include <utilities/Poller/MapPoller.h>

using namespace std;

MapPoller::MapPoller()
{
}

MapPoller::~MapPoller()
{
}

void MapPoller::notifyBuildingSelected(Building *building)
{
	list<MapObserver *> observers = getObservers();
	list<MapObserver *>::iterator elt;
	for (elt = observers.begin(); elt != observers.end(); elt++)
	{
		if ((*elt)->onBuidingClicked(building))
			break;
	}
}

void MapPoller::Poll()
{
}