////////////////////////////////////////////////////////////////////////////////
// File Name: singleton.hpp                                                   //
// Author: Lior Cohen                                                         //
// Date 29/07/2020                                                            //
// Purpose: header file for the singleton                                     //
// Code Reviewer: Amir Saraf                                                  //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_8586_SINGELTON_HPP
#define ILRD_8586_SINGELTON_HPP

#include <iostream>
#include <atomic>
#include <boost/atomic.hpp>

#include "boost/core/noncopyable.hpp"

template <typename T>
class Singleton: private boost::noncopyable
{
public:

    static T* GetInstance();
    static void CleanUp();

private:
    Singleton();
    static T *m_instance;
    static int m_init;
    
};

template <typename T> 
T* Singleton<T>::m_instance = NULL;

template <typename T>
int Singleton<T>::m_init = 0;


template <typename T>
T* Singleton<T>::GetInstance()
{    
    if (NULL == m_instance)
    {
        bool go = false;
        if (0 == __atomic_fetch_or(&m_init, 1, __ATOMIC_SEQ_CST))
        {
            __atomic_store_n(&m_instance, new T, __ATOMIC_SEQ_CST);
            go = true;
        }
        else
        {
            while (false == go)
            ;
        }
    }

    return m_instance;
}

template <typename T> 
void Singleton<T>::CleanUp()
{
    delete m_instance;
}


#endif // ILRD_8586_SINGELTON_HPP