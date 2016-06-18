#ifndef VILLAGE_H
#define VILLAGE_H
#include <model/Map.h>

class Village
{
	private:
		unsigned int m_population;
		unsigned int m_housed_population;
		unsigned int m_housing_capacity;
		unsigned int m_schooled_population;
		unsigned int m_workers;
		unsigned int m_workers_capacity;
		unsigned int m_food;
		unsigned int m_merit;
		int m_favor;
		int m_weight_contribution;
		Map *m_map;

	public:
		Village();
		~Village();

		void distributePopulation();
		unsigned int getPopulation();
		void setPopulation(unsigned int population);
		unsigned int getHousedPopulation();
		void setHousedPopulation(unsigned int population);
		unsigned int getSchooledPopulation();
		void setSchooledPopulation(unsigned int population);
		unsigned int getHousingCapacity();
		void setHousingCapacity(unsigned int housing);
		unsigned int getWorkers();
		void setWorkers(unsigned int workers);
		unsigned int getWorkersCapacity();
		void setWorkersCapacity(unsigned int workers);
		unsigned int getFood();
		void setFood(unsigned int food);
		void sendFood(unsigned int amount);
		unsigned int getMerit();
		void setMerit(unsigned int merit);
		int getFavor();
		void setFavor(int favor);
		void addBuilding(Building *building);
		void destroyBuilding(Building *building);
		int getWeightContribution();
		void setWeightContribution(int weigth_contribution);
		Map *getMap();
		void setMap(Map *game_map);
		void managePopulation();
};
#endif // VILLAGE_H
