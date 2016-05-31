#include <iostream>
#include <Constants.hpp>
#include <utilities/RessourceManager.h>
#include <model/Building.hpp>
#include <model/Farm.hpp>

using namespace std;

Farm::Farm(MainWindow *prt) : Building(prt)
{

    Building::setName("Farm");
    Building::setHeight(50);
    Building::setWidth(50);
}

Farm::~Farm()
{
}
