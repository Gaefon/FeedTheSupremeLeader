#ifndef OBSERVER_H
#define OBSERVER_H


class Observer
{
	public:
		Observer();
		virtual ~Observer();
		virtual void Respond() = 0;

	protected:

	private:
};

#endif // OBSERVER_H
