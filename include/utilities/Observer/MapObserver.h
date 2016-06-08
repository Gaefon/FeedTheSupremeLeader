#ifndef MAP_OBSERVER_H
#define MAP_OBSERVER_H

#include <model/Building.hpp>

class MapObserver
{
	public:
		MapObserver() {}
		~MapObserver() {}
		virtual bool onBuidingClicked(Building *building) = 0;
		virtual bool onBuildingBuilt(Building *building) = 0;
};

#endif
