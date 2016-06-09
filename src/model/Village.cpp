#include <model/Village.h>
#include <Constants.hpp>
#include <iostream>

using namespace std;

Village::Village()
{
   // m_map = game_map;
    m_population = STARTING_POPULATION;
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
unsigned int Village::getSchooledPopulation()
{
    return m_schooled_population;

}
void Village::setSchooledPopulation(unsigned int population)
{
    m_schooled_population = population;
}


unsigned int Village::getWorkers()
{
    return m_population;
}

void Village::setWorkers(unsigned int workers)
{
    m_workers = workers;
}
unsigned int Village::getFood()
{
    return m_food;
}
void Village::setFood(unsigned int food)
{
    m_food = food;
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

