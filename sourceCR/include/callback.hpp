////////////////////////////////////////////////////////////////////////////////
// File Name: callback.hpp                                                    //
// Author: Lior Cohen                                                         //
// Date 12/07/2020                                                            //
// Purpose: header file for the callback class                                //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_CALLBACK_HPP
#define ILRD_RD8586_CALLBACK_HPP

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "dispatcher.hpp"

namespace ilrd
{

static void EmptyFunction()
{}

template <typename DISPATCHER>
class Callback : private boost::noncopyable
{
public:
    typedef boost::function< void(typename DISPATCHER::DataType) > NotifyPointer;
    typedef boost::function< void() > StopInformPointer;

    Callback(const NotifyPointer& func,
             const StopInformPointer& stop_inform_func = EmptyFunction); 

    ~Callback();

private:
    void Link(DISPATCHER* dispatcher);
    void Unlink();
    void Invoke(typename DISPATCHER::DataType data);

    DISPATCHER* m_dispatcher;
    NotifyPointer m_callback_func;
    StopInformPointer m_stop_inform_func; 

    
    struct FriendHelper{typedef DISPATCHER MyDispatcher;};
    friend class FriendHelper::MyDispatcher;
};

///////////////////////////////////////////////////////////////////////////////
///   inline / template functions implementation   /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename DISPATCHER>
Callback<DISPATCHER>::Callback(const NotifyPointer& func,
const StopInformPointer& stop_inform_func) : 
                m_callback_func(func),m_stop_inform_func(stop_inform_func)
{}


template <typename DISPATCHER>
Callback<DISPATCHER>::~Callback()
{
    if (m_dispatcher)
    {
        m_dispatcher->Unsubscribe(this);
    }
}

template <typename DISPATCHER>
void Callback<DISPATCHER>::Link(DISPATCHER *dispatch)
{
    m_dispatcher = dispatch;
}

template <typename DISPATCHER>
void Callback<DISPATCHER>::Unlink()
{
    m_dispatcher = 0;
}

template <typename DISPATCHER>
void Callback<DISPATCHER>::Invoke(typename DISPATCHER::DataType data)
{
    m_callback_func(data);
}

} // namespace ilrd

#endif // ILRD_RD8586_CALLBACK_HPP