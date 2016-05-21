#include <utilities/Poller/EventPoller.h>

using namespace std;

template<class T>
int EventPoller<T>::unSubscribe(T obs)
{
	mObserverList.remove(obs);
	return 0;
}

