#ifndef VILLAGE_H
#define VILLAGE_H

class Village
{
    private:
        unsigned int m_population;
        unsigned int m_workers;
        unsigned int m_food;
        int m_merit;
        int m_favor;
        int m_weight_contribution;


    public:
        Village();
        ~Village();

        unsigned int getPopulation();
        void setPopulation(unsigned int population);
        unsigned int getWorkers();
        void setWorkers(unsigned int workers);
        unsigned int getFood();
        void setFood(unsigned int food);
        int getMerit();
        void setMerit(int merit);
        int getFavor();
        void setFavor(int favor);
        int getWeightContribution();
        void setWeightContribution(int weigth_contribution);
};
#endif // VILLAGE_H
