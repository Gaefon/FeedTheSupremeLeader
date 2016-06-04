#include <utilities/BuildingHelper.h>

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