#include <iostream>
#include <SDL.h>

#include <FeedTheSupremLeader.h>
#include <uiclass/GameInterface.h>
#include <uiclass/GameMenuDialog.h>
#include <utilities/Timer.h>

#include <utilities/Poller/SDLPoller.h>
#include <model/Village.h>
#include <Constants.hpp>

using namespace std;

void showGame(MainWindow *window)
{
	SDLPoller poller;
	Village village;
	GameInterface game_iface(window, &poller, &village);
	GameMenuDialog game_menu(window, &game_iface, &poller, 300, 200);
	int iteration = 0;

	poller.subscribe(window);
	poller.subscribe(&game_menu);
	Timer::getInstance()->setLastTime(SDL_GetTicks());
	while (!window->hasCloseRequest() && !game_menu.isGotoMenuRequested())
	{
		iteration += FRAME_PAUSE_DURATION;
		poller.Poll();
		window->clear();
		game_iface.draw();
		game_menu.draw();
		window->update();
		Timer::getInstance()->getTimeDifference();
		if (iteration >= 5000)
		{
			iteration = 0;
			village.setHousingCapacity(0);
			village.setWorkersCapacity(0);
			list<Building *>::iterator it;
			for (it =  village.getMap()->getBuildings()->begin(); it !=  village.getMap()->getBuildings()->end(); it++)
			{
				(*it)->onVillageUpdateRequest(&village);
			}
			village.managePopulation();
			cout << "-----------------------VILLAGE-------------------------" << endl;   
			cout << "merit : " << village.getMerit() << endl;
			cout << "food : " << village.getFood() << endl;
			cout << "total population : " << village.getPopulation() << endl;
			cout << "housed population : " << village.getHousedPopulation() << endl;
			cout << "housing capacity : " << village.getHousingCapacity() << endl;
			cout << "bums : " << (village.getPopulation() - village.getHousedPopulation()) << endl;
			cout << "workers capacity : " << village.getWorkersCapacity() << endl;
			cout << "workers : " << village.getWorkers() << endl;
			cout << "wankers : " << (village.getPopulation() - village.getWorkers()) << endl;
			cout << "-------------------------------------------------------" << endl;
		}
	}
}

