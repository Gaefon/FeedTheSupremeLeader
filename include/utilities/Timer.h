#ifndef TIMER_H
#define TIMER_H

#include <utilities/Singleton.hpp>

class Timer : public Singleton<Timer>
{
	friend class Singleton<Timer>;

	private:
		long m_last_time;
		Timer();

	public:
		void setLastTime(long last_time);
		long getLastTime();
		void getTimeDifference();
};

#endif
