#ifndef BUILDING_HELPER_H
#define BUILDING_HELPER_H

#include <list>
#include <model/Building.hpp>

class BuildingHelper
{
	public:
		static bool isBuildingPlaceValid(std::list<Building *> list_building, Building *building);
};

#endif