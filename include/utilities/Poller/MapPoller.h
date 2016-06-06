#ifndef MAPPOLLER_H
#define MAPPOLLER_H

#include <model/Building.hpp>
#include <utilities/Poller/EventPoller.h>
#include <utilities/Observer/MapObserver.h>


class MapPoller : public EventPoller<MapObserver *>
{
	public:
		MapPoller();
		~MapPoller();
		void notifyBuildingSelected(Building *building);
		void Poll();
};

#endif