#include <model/Village.h>
#include <Constants.hpp>
#include <iostream>

using namespace std;

Village::Village()
{
	m_population = STARTING_POPULATION;
	m_schooled_population = 0;
	m_housed_population = 0;
	m_housing_capacity = 0;
	m_workers = 0;
	m_food = STARTING_FOOD;
	m_merit = STARTING_MERIT;
	m_favor = STARTING_FAVOR;
	m_weight_contribution = 0;
}

Village::~Village()
{
}
unsigned int Village::getPopulation()
{
	return m_population;
}
void Village::setPopulation(unsigned int population)
{
	m_population = population;
}

unsigned int Village::getHousedPopulation()
{
	return m_housed_population;
}
void Village::setHousedPopulation(unsigned int population)
{
	m_housed_population = population;
}
unsigned int Village::getSchooledPopulation()
{
	return m_schooled_population;
}

void Village::setHousingCapacity(unsigned int capacity)
{
	m_housing_capacity = capacity;
}
unsigned int Village::getHousingCapacity()
{
	return m_housing_capacity;
}

void Village::setSchooledPopulation(unsigned int population)
{
	m_schooled_population = population;
}

unsigned int Village::getWorkers()
{
	return m_workers;
}

void Village::setWorkers(unsigned int workers)
{
	m_workers = workers;
}

unsigned int Village::getWorkersCapacity()
{
	return m_workers_capacity;
}

void Village::setWorkersCapacity(unsigned int workers)
{
	m_workers_capacity = workers;
}

unsigned int Village::getFood()
{
	return m_food;
}
void Village::setFood(unsigned int food)
{
	m_food = food;
}

void Village::sendFood(unsigned int amount)
{
	m_food = m_food - amount;
	m_merit += amount * MERIT_FOOD_FACTOR;
}

int Village::getMerit()
{
	return m_merit;
}
void Village::setMerit(int merit)
{
	m_merit = merit;
}
int Village::getFavor()
{
	return m_favor;
}
void Village::setFavor(int favor)
{
	m_favor = favor;
}
int Village::getWeightContribution()
{
	return m_weight_contribution;
}
void Village::setWeightContribution(int weight_contribution)
{
	m_weight_contribution = weight_contribution;
}

Map *Village::getMap()
{
	return m_map;
}
void Village::setMap(Map *game_map)
{
	m_map = game_map;
}

void Village::distributePopulation()
{
	list<Building *>::iterator it;

	while (m_population > m_housed_population && m_housed_population < m_housing_capacity)
	{
		for (it = getMap()->getBuildings()->begin(); it != getMap()->getBuildings()->end() && m_population > m_housed_population; it++)
		{
			if((*it)->getMaxOccupancy() - (*it)->getOccupancy() > 0)
			{
				(*it)->setOccupancy((*it)->getOccupancy() + 1);
				m_housed_population++;
			}
		}
	}

	while (m_population > m_workers && m_workers < m_workers_capacity)
	{
		for (it = getMap()->getBuildings()->begin(); it != getMap()->getBuildings()->end() && m_population > m_workers; it++)
		{
			if((*it)->getMaxWorkers() - (*it)->getWorkers() > 0)
			{
				(*it)->setWorkers((*it)->getWorkers() + 1);
				m_workers++;
			}
		}
	}
}

void Village::managePopulation()
{
	float base_growth = m_population * 0.03f;

	if (m_population == 0)
	{
		m_population = m_housing_capacity / 2;
	}
	else if (m_housing_capacity > m_population)
	{
		float base_immigration = (m_housing_capacity - m_population) * HOUSING_ATTRACTIVENESS;
		float bonus_immigration = base_immigration * (1 + (m_merit / MAX_MERIT * 3 + m_favor / MAX_FAVOR) / 4);
		float immigrated_population = base_immigration  + bonus_immigration;
		m_population = m_population + immigrated_population;
	}
	m_population = m_population + base_growth;
	distributePopulation();
}

