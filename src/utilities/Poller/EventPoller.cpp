#include <list>
#include <utilities/Poller/Observer.h>
#include <utilities/Poller/EventPoller.h>

using namespace std;

EventPoller::EventPoller()
{
    //ctor
}

EventPoller::~EventPoller()
{
    //dtor
}

int EventPoller::subscribe(Observer *obs)
{
	list<Observer *>::const_iterator iterator;
	for(iterator = mObserverList.begin(); iterator != mObserverList.end(); ++iterator)
	{
		if(obs == *iterator)
		{
			//TODO : Gestion des messages d'erreurs (ALREADY SUBSCRIBED);
			return -1;
		}
	}
	mObserverList.push_front(obs);
	return 0;
}

int EventPoller::unSubscribe(Observer *obs)
{
	mObserverList.remove(obs);
	return 0;
}

void EventPoller::notify()
{
	list<Observer *>::const_iterator iterator;
	for(iterator = mObserverList.begin(); iterator != mObserverList.end(); ++iterator)
	{
		// here
	}
}
