#ifndef SINGLETON_H
#define SINGLETON_H
template <class T> class Singleton
{
    public :
        static T &GetInstance();

    protected :
        static T m_instance;

    private :
        T &operator = (const T&) {}
};

#endif // SINGLETON_H
