#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
	public:
		// le getInstance
		static T *getInstance()
		{
			if (m_instance == NULL)
				m_instance = new T(); // au premier appel de getInstance on instancie le singleton
			return (static_cast<T*> (m_instance));
		}

	private:
		static T *m_instance;

	protected :
		Singleton() {};
		~Singleton() {};
};

template <typename T>
T *Singleton<T>::m_instance = NULL;

#endif // SINGLETON_H
