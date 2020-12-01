////////////////////////////////////////////////////////////////////////////////
// File Name: callback.hpp                                                    //
// Author: Lior Cohen                                                         //
// Date 12/07/2020                                                            //
// Purpose: header file for the callback class                                //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_CALLBACK2_HPP
#define ILRD_RD8586_CALLBACK2_HPP

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "source.hpp"

namespace ilrd
{

namespace detail
{

    inline void EmptyFunction()
    {
    }

} // namespace detail


template < typename SOURCE >
class Callback : private boost::noncopyable
{
public:
    typedef boost::function< void(typename SOURCE::DataType) > NotifyPointer;
    typedef boost::function< void() > StopInformPointer;

    // Ctor
    Callback(const NotifyPointer& func,
             const StopInformPointer& stop_inform_func = detail::EmptyFunction);

    // Dtor - Unlink the m_source Source.
    ~Callback();

private:
    // struct FriendHelper
    // {
    //     typedef SOURCE MySource;
    // };
    // friend class FriendHelper::MySource;
    friend SOURCE;

    // Link - link source-subject to the callback observer
    void Link(SOURCE* source);

    // Unlink - unlink source-subject from the callback observer
    void Unlink();

    // Invoke - invoke Callback function with data.
    void Invoke(typename SOURCE::DataType data);

private:
    SOURCE* m_source;
    const NotifyPointer m_func;
    const StopInformPointer m_stop_inform_func;
};
////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template < typename SOURCE >
Callback< SOURCE >::Callback(const NotifyPointer& func,
                             const StopInformPointer& stop_inform_func)
    : m_source(NULL), m_func(func), m_stop_inform_func(stop_inform_func)
{
}

template < typename SOURCE >
Callback< SOURCE >::~Callback()
{
    if (m_source)
    {
        m_source->Unsubscribe(this);
    }
}

template < typename SOURCE >
void Callback< SOURCE >::Link(SOURCE* source)
{
    assert(source);
    assert(!m_source);
    
    m_source = source;
}

template < typename SOURCE >
void Callback< SOURCE >::Unlink()
{
    assert(m_source);

    m_source = NULL;
    m_stop_inform_func();
}

template < typename SOURCE >
void Callback< SOURCE >::Invoke(typename SOURCE::DataType data)
{
    assert(m_source);

    m_func(data);
}

} // namespace ilrd

#endif /* ILRD_RD8586_CALLBACK2_HPP */
