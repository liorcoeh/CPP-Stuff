////////////////////////////////////////////////////////////////////////////////
// File Name: dispatcher.hpp                                                  //
// Author: Lior Cohen                                                         //
// Date 26/08/2020                                                            //
// Purpose: header file for the dispatcher class                              //
// Code Reviewer:                                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef __ILRD_RD8586_DISPATCHER_HPP__
#define __ILRD_RD8586_DISPATCHER_HPP__

#include <iostream>
#include <assert.h>
#include <boost/function.hpp> /* function */
#include <boost/noncopyable.hpp> //non-copyable classes
#include <iterator>
#include <list>

#include "logger.hpp"

namespace ilrd
{

template <typename DISPATCHER>
class Callback;

template <typename T>
class Dispatcher : private boost::noncopyable
{
public:
    Dispatcher()
    {}

    ~Dispatcher();
    typedef T DataType; // nested type for internal & external use

    void Subscribe(Callback<Dispatcher<T>>* callback);
    void Unsubscribe(Callback<Dispatcher<T>>* callback);
    void Notify(DataType data);

private:
    std::list<Callback<Dispatcher<T>>*> m_callbacks;
};

////////////////////////////////////////////////////////////////////////////////
///   inline / template functions implementation   /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename T>
void Dispatcher<T>::Subscribe(Callback<Dispatcher<T>> *callback)
{
    m_callbacks.push_front(callback);
    callback->Link(this);
}

template <typename T>
void Dispatcher<T>::Unsubscribe(Callback<Dispatcher<T>> *callback)
{
    m_callbacks.remove(callback);
    callback->Unlink();
}

template <typename T>
void Dispatcher<T>::Notify(DataType data)
{
    typename std::list<Callback<Dispatcher<T>> *>::iterator iter = m_callbacks.begin();

    for (iter; iter != m_callbacks.end(); ++iter)
    {
        (*iter)->Invoke(data);
    }
}

template <typename T>
Dispatcher<T>::~Dispatcher()
{
    typename std::list<Callback<Dispatcher<T>> *>::iterator iter;

    for (iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter)
    {
        (*iter)->Unlink();
    }
}

} // namespace ilrd

#endif // __ILRD_RD8586_DISPATCHER_HPP__