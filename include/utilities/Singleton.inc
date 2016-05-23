#include <iostream>
#include <utilities/Singleton.hpp>
#include <uiclass/InterfaceSetup.hpp>

template <class T> T Singleton<T>::m_instance = T();

template <class T> T &Singleton<T>::GetInstance()
{
    return m_instance;
}
