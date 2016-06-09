#ifndef VILLAGE_OBSERVER_H
#define VILLAGE_OBSERVER_H
#include <model/Village.h>
//class Village;

class VillageObserver
{
	public:
		VillageObserver() {}
		~VillageObserver() {}
		virtual bool onVillageUpdateRequest(Village *village) = 0;
};

#endif
