#include <iostream>
#include <utilities/Timer.h>
#include <SDL.h>
#include <Constants.hpp>

using namespace std;

Timer::Timer()
{
  m_last_time = 0;
}

long Timer::getLastTime()
{
	return m_last_time;
}

void Timer::setLastTime(long last_time)
{
	m_last_time = last_time;
}

void Timer::getTimeDifference()
{
	int current_time = SDL_GetTicks();
	long timeTmp;

	timeTmp = current_time - m_last_time;
	if (timeTmp > FRAME_PAUSE_DURATION)
	{
		timeTmp = FRAME_PAUSE_DURATION;
		cerr << "Pause too long" << endl;
	}
	//SDL_Delay(FRAME_PAUSE_DURATION - timeTmp);
	m_last_time = current_time;
}
