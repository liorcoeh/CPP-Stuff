////////////////////////////////////////////////////////////////////////////////
// File Name: fd_timer.hpp                                                    //
// Author: Lior Cohen                                                         //
// Date 26/07/2020                                                            //
// Purpose: header file for the file descriptor timer (reactor) assignment    //
// Code Reviewer: Alistair Hudson                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef __ILRD_RD8586_FD_TIMER_HPP__
#define __ILRD_RD8586_FD_TIMER_HPP__

#include <boost/chrono.hpp>      // boost::chrono
#include <boost/noncopyable.hpp> // boost::noncopyable

#include "reactor.hpp"          // Reactor class
#include "scheduler_detail.hpp" // scheduler detail utility namespace
#include "logger.hpp"

namespace ilrd
{

class FDTimer : private boost::noncopyable
{
public:
    // typedefs for inner types
    typedef Callback<Dispatcher<int>>::NotifyPointer ActionFunc;
    typedef detail::MicroSecs MicroSecs;

    // FDTimer Constructor
    // Receives: reactor - a reference to a reactor to work with
    //           callback_func - a handler function to invoke when the reactor
    //                           calls timer file descriptors' handler
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             created
    explicit FDTimer(Reactor& reactor, ActionFunc callback_func);

    // FDTimer Destructor
    // Exceptions: no exceptions
    ~FDTimer();

    // Set
    // Receives: microseconds - a chrono::microseconds object with the time
    //           requested from now
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void Set(MicroSecs microseconds);

    // Unset
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void Unset();

private:
    inline void UpdateReactorDead();

    Reactor* m_reactor;
    Callback<Dispatcher<int>> m_callback;
    int m_fd;
};

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

inline void FDTimer::UpdateReactorDead()
{
    LOG_WARNING("reactor is not alive");
    m_reactor = NULL;
}
} // namespace ilrd

#endif /* ILRD_RD8586_FD_TIMER_HPP */