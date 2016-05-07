#ifndef EVENTPOLLER_H
#define EVENTPOLLER_H


class EventPoller
{
    public:
        EventPoller();
        virtual ~EventPoller();
        int subscribe(Observer *obs);
        int unSubscribe(Observer *obs);
        virtual void Poll() = 0;

    protected:
        void notify();
        std::list<Observer *> mObserverList;
};

#endif // EVENTPOLLER_H
