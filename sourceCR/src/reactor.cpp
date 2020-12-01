////////////////////////////////////////////////////////////////////////////////
// File Name: reacotr.cpp                                                     //
// Author: Lior Cohen                                                         //
// Date 15/07/2020                                                            //
// Purpose: functions file for the reactor                                    //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>         // transform
#include <boost/foreach.hpp> // BOOST_FOREACH

#include "reactor.hpp" // reactor class

using namespace ilrd;
using namespace detail;
using namespace std;

Reactor::Reactor(ListenerInterface* listener)
    : m_listener(listener), m_toStop(false)
{
}

void Reactor::Add(Handle handle, MODE mode, ReactorCallback* callback)
{
    std::ostringstream log;
    log << "Reactor::Add - adding callback to fd " << handle << ", with mode "
        << mode;
    LOG_INFO(log.str());

    m_eventHandlers[HandleAndMode(handle, mode)].m_dispatcher.Subscribe(
        callback);
}

void Reactor::Remove(Handle handle, MODE mode, ReactorCallback* callback)
{
    std::ostringstream log;
    log << "Reactor::Remove - removing callback from fd" << handle
        << ", with mode " << mode;
    LOG_INFO(log.str());

    m_eventHandlers[HandleAndMode(handle, mode)].m_dispatcher.Unsubscribe(
        callback);
}

void Reactor::Run()
{
    LOG_INFO("Reactor::Run");
    // handle situation when Stop() called before Run()
    m_toStop = false;

    while (!m_toStop && !m_eventHandlers.empty())
    {
        vector< HandleAndMode > handlesSnd;
        vector< HandleAndMode > handlesRec;

        // add map keys to a vector
        std::transform(m_eventHandlers.begin(), m_eventHandlers.end(),
                       std::back_inserter(handlesSnd), detail::GetHandle());

        // call listen
        handlesRec = m_listener->Listen(handlesSnd);
        LOG_INFO(
            "Reactor::Run - one or more file descriptors are ready to be read");

        // call all the callback functions for the handles that received in
        // handlesRec
        std::for_each(handlesRec.begin(), handlesRec.end(),
                      detail::InvokeHandlers(m_eventHandlers));
    }
}

void Reactor::Stop()
{
    LOG_INFO("Reactor::Stop");

    m_toStop = true;
}