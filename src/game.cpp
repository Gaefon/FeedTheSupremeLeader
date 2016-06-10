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
    GameMenuDialog game_menu(window, &poller, 300, 200);
    GameInterface game_iface(window, &poller, &village);
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
            list<Building *>::iterator it;
            for (it =  village.getMap()->getBuildings()->begin(); it !=  village.getMap()->getBuildings()->end(); it++)
            {
                (*it)->onVillageUpdateRequest(&village);
            }

            village.managePopulation();
            cout << village.getPopulation() << endl;
            cout << village.getHousedPopulation() << endl;
        }
    }
}
