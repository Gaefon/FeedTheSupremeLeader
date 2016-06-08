#ifndef EVENTPOLLER_H
#define EVENTPOLLER_H

#include <list>
#include <utilities/Observer/SdlObserver.h>

template<class T>
class EventPoller
{
	public:
		EventPoller() {}
		virtual ~EventPoller() {}
		int subscribe(T obs)
		{
			typename std::list<T>::iterator it;
			for (it = mObserverList.begin(); it != mObserverList.end(); it++)
			{
				if (obs == *it)
					return -1;
			}
			mObserverList.push_front(obs);
			return 0;
		}

		int unSubscribe(T obs)
		{
			mObserverList.remove(obs);
			return 0;
		}
	protected:
		std::list<T> getObservers()
		{
			return mObserverList;
		}

	private:
		std::list<T> mObserverList;
};

#endif // EVENTPOLLER_H
