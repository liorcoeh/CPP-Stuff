////////////////////////////////////////////////////////////////////////////////
// File Name: source_.hpp                                                     //
// Author: Lior Cohen                                                         //
// Date 12/07/2020                                                            //
// Purpose: header file for the source source class                           //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_OBSERVABLE_SOURCE_HPP
#define ILRD_RD8586_OBSERVABLE_SOURCE_HPP

#include <assert.h>              // assert
#include <boost/noncopyable.hpp> //boost::noncopyable
#include <iostream>              // cerr

#define LOG_ERR(X) (std::cerr << "ERROR: " << (X) << std::endl)
#define LOG_WRN(X) (std::cerr << "WARNING: " << (X) << std::endl)

namespace ilrd
{

template < typename SOURCE >
class Callback;

template < typename T >
class Source : private boost::noncopyable
{
public:
    Source();
    ~Source();
    typedef T DataType; // nested type for internal & external use

    // Subscribe - subscribe a new observer to the subject
    //       Receive: callback - pointer to a Callback object of type Source<T>
    void Subscribe(Callback< Source< T > >* callback);
    // Unsubscribe - unsubscribe an observer to the subject
    //       Receive: callback - pointer to a Callback object of type Source<T>
    void Unsubscribe(Callback< Source< T > >* callback);
    // Notify - notify all the observers of a subject state change
    //       Receive: data - data of type T to send as an argument to the
    //       callback
    void Notify(DataType data);

    bool operator==(Callback< Source< T > >* other_callback);

private:
    Callback< Source< T > >* m_callback;
};

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template < typename T >
Source< T >::Source() : m_callback(NULL)
{
}

template < typename T >
Source< T >::~Source()
{
    if (m_callback)
    {
        m_callback->Unlink();
    }
}

template < typename T >
void Source< T >::Subscribe(Callback< Source< T > >* callback)
{
    assert(callback);
    assert(!m_callback);

    m_callback = callback;
    m_callback->Link(this);
}

template < typename T >
void Source< T >::Unsubscribe(Callback< Source< T > >* callback)
{
    assert(callback);
    assert(m_callback);

    if (m_callback == callback)
    {
        m_callback->Unlink();
        m_callback = NULL;
    }
}

template < typename T >
void Source< T >::Notify(DataType data)
{
    if (m_callback)
    {
        m_callback->Invoke(data);
    }
    else
    {
        LOG_WRN("Source is not subscribed to a callback");
    }
}

template < typename T >
bool Source< T >::operator==(Callback< Source< T > >* other_callback)
{
    return (m_callback == other_callback);
}
} // namespace ilrd

#endif /* ILRD_RD8586_OBSERVABLE_SOURCE_HPP */
