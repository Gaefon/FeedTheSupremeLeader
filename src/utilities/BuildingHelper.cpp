#include <utilities/BuildingHelper.h>
#include <model/Farm.hpp>
#include <model/House.h>
#include <model/Road.h>
#include <model/Building.hpp>
#include <model/School.h>

using namespace std;

bool BuildingHelper::isBuildingPlaceValid(list<Building *> list_building, Building *building)
{
	unsigned int build_bottom;
	unsigned int tmp_bottom;
	unsigned int build_right;
	unsigned int tmp_right;

	for (list<Building *>::iterator it = list_building.begin(); it != list_building.end(); ++it)
	{
		build_bottom = building->getPosY() + building->getHeight();
		tmp_bottom = (*it)->getPosY() + (*it)->getHeight();
		build_right = building->getPosX() + building->getWidth();
		tmp_right = (*it)->getPosX() + (*it)->getWidth();
		//horizontal edge
		if ((
				(building->getPosY() >= (*it)->getPosY() && building->getPosY() < tmp_bottom) ||
				(build_bottom > (*it)->getPosY() && build_bottom <= tmp_bottom)
			)
			&&
			(
				(building->getPosX() >= (*it)->getPosX() && building->getPosX() < tmp_right) ||
				(build_right > (*it)->getPosX() && build_right <= tmp_right)
			)
		)
		{
			return false;
		}
	}
	return true;
}

Building * BuildingHelper::getCopyOfTmpBuilding(Building *tmp_building, MainWindow *m_parent)	{
	if (dynamic_cast<Farm*>(tmp_building) != NULL)	{
		return new Farm(m_parent);
  }	else if (dynamic_cast<House*>(tmp_building) != NULL)	{
		return new House(m_parent);
	} else if (dynamic_cast<Road*>(tmp_building) != NULL)	{
		return new Road(m_parent);
	} else if (dynamic_cast<School*>(tmp_building) != NULL)	{
		return new School(m_parent);
	}
	return NULL;
}
