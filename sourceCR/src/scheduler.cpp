////////////////////////////////////////////////////////////////////////////////
// File Name: scheduler.cpp                                                   //
// Author: Lior Cohen                                                         //
// Date 26/07/2020                                                            //
// Purpose: functions file for the scheduler (reactor)                        //
// Code Reviewer: Alistair Hudson                                             //
////////////////////////////////////////////////////////////////////////////////

#include <boost/bind.hpp>                 // bind
#include <boost/chrono.hpp>               // chrono things
#include <boost/chrono/system_clocks.hpp> // chrono::system_clock
#include <cassert>

#include "scheduler.hpp" // scheduler class

using namespace ilrd;
using namespace std;
using namespace detail;

Scheduler::Scheduler(Reactor& reactor)
try : m_timer(reactor, boost::bind(&Scheduler::InvokeCurrentTask, this, _1))
{
}
catch (...)
{
    throw std::runtime_error("scheduler create failed");
}

void Scheduler::ScheduleAction(MicroSecs microseconds, ActionFunc function)
{
    ScheduleAction(Now() + microseconds, function);
}

void Scheduler::ScheduleAction(TimePoint timepoint, ActionFunc function)
{
    Task new_task = {timepoint, function};
    m_tasks.push(new_task);

    if (IsSetTimerNeeded(new_task))
    {
        SetTimer(GetDuration(timepoint));
    }
}

void Scheduler::InvokeCurrentTask(int fd)
{
    assert(!m_tasks.empty());
    const Task current = m_tasks.top();
    m_tasks.pop();

    current.m_function(fd);

    if (!m_tasks.empty())
    {
        SetTimer(GetDurationForNextTask());
    }
    else
    {
        m_timer.Unset();
    }
}

bool Scheduler::IsSetTimerNeeded(Task& new_task) const
{
    return (m_tasks.top().m_timepoint == new_task.m_timepoint);
}

void Scheduler::SetTimer(MicroSecs time)
{
    try
    {
        m_timer.Set(time);
    }
    catch (runtime_error&)
    {
        m_tasks.pop(); // pop added task that couldn't set the FDTimer
        throw std::runtime_error("can't add action to scheduler");
    }
}