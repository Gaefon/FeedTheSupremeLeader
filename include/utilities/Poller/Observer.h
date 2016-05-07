#ifndef OBSERVER_H
#define OBSERVER_H


class Observer
{
    public:
        virtual void Respond() = 0;
        Observer();
        virtual ~Observer();

    protected:

    private:
};

#endif // OBSERVER_H
