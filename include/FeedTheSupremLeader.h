#ifndef FEED_THE_SUPREM_LEADER_H
#define FEED_THE_SUPREM_LEADER_H

#include <uiclass/MainWindow.hpp>
#include <utilities/Poller/SDLPoller.h>

void showMenu(MainWindow *window, SDLPoller *main_poller);
void showParameters(MainWindow *window, SDLPoller *main_poller);
void showGame(MainWindow *window, SDLPoller *main_poller);

#endif