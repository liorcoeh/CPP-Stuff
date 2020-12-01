////////////////////////////////////////////////////////////////////////////////
// File Name: fd_timer.cpp                                                    //
// Author: Lior Cohen                                                         //
// Date 26/07/2020                                                            //
// Purpose: functions file for the file descriptor timer (reactor)            //
// Code Reviewer: Alistair Hudson                                             //
////////////////////////////////////////////////////////////////////////////////

extern "C"
{
#include <sys/timerfd.h> // timerfd_create, timerfd_set
}
#include <boost/bind.hpp>                 // boost::bind
#include <boost/chrono/system_clocks.hpp> // boost::chrono::system_clock

#include "fd_timer.hpp" // FDTimer Class

using namespace ilrd;
using namespace std;
using namespace detail;

FDTimer::FDTimer(Reactor& reactor, ActionFunc callback_func)
    : m_reactor(&reactor),
      m_callback(callback_func, boost::bind(&FDTimer::UpdateReactorDead, this)),
      m_fd(timerfd_create(CLOCK_MONOTONIC, 0))
{
    if (m_fd < 0)
    {
        throw std::runtime_error("can't create timerfd");
    }

    try
    {
        m_reactor->Add(m_fd, detail::READ, &m_callback);
    }
    catch (...)
    {
        close(m_fd);
        throw std::runtime_error("can't add to reactor");
    }
}

FDTimer::~FDTimer()
{
    if (m_reactor)
    {
        m_reactor->Remove(m_fd, detail::READ, &m_callback);
    }
    close(m_fd);
}

void FDTimer::Set(MicroSecs microseconds)
{
    if (microseconds.count() < 0)
    {
        microseconds = MicroSecs(1);
    }

    // create itimerspec struct for the time given
    struct itimerspec timerSpec;
    memset(&timerSpec, 0, sizeof(timerSpec));
    timerSpec.it_value.tv_sec = MicroToSecs(microseconds);
    timerSpec.it_value.tv_nsec = MicroToNanos(microseconds);

    if (timerfd_settime(m_fd, 0, &timerSpec, NULL) < 0)
    {
        throw std::runtime_error("can't set timerfd");
    }
}

void FDTimer::Unset()
{
    struct itimerspec timerSpec;
    memset(&timerSpec, 0, sizeof(timerSpec));

    if (timerfd_settime(m_fd, 0, &timerSpec, NULL) < 0)
    {
        throw std::runtime_error("can't clear timerfd");
    }
}