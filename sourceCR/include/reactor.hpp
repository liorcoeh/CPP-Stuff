////////////////////////////////////////////////////////////////////////////////
// File Name: reacotr.hpp                                                     //
// Author: Lior Cohen                                                         //
// Date 15/07/2020                                                            //
// Purpose: header file for the reactor                                       //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_REACTOR_HPP
#define ILRD_RD8586_REACTOR_HPP

#include <boost/shared_ptr.hpp>
#include <map> // map stl

#include "listener_interface.hpp" // reactor interface class
#include "reactor_detail.hpp"     // reactor detail namespace
#include "boost/core/noncopyable.hpp"         // class uncopyable

namespace ilrd
{

class Reactor : private boost::noncopyable
{
public:
    // Ctor - listener will be deleted by the object Dtor!:
    Reactor(ListenerInterface* listener); // Ctor

    typedef detail::ReactorCallback ReactorCallback;

    // Add - adds a handle and callback function handler into the Reactor
    //       Receive: handle - file descriptor, mode - mode for file descriptor,
    //       func - function callback pointer that receives int and return void.
    //       Return: function uid.
    void Add(detail::Handle handle, detail::MODE mode,
             ReactorCallback* callback);

    // Remove - remove a callback function from the Reactor
    //       Receive: handle - file descriptor, mode - mode for file descriptor,
    //       func_uid - function uid of the function to remove
    void Remove(detail::Handle handle, detail::MODE mode,
                ReactorCallback* callback);

    // Run - start the Reactor operation. stops when there are no handles left
    //       or when Stop() is called
    void Run();

    // Stop - stops the Reactor operation. can be called just from inside one of
    //        the handlers callback functions
    void Stop();

private:
    std::map< detail::HandleAndMode, detail::DispatcherClass > m_eventHandlers;
    boost::shared_ptr< ListenerInterface > m_listener;
    bool m_toStop;
};

} // namespace ilrd

#endif /* ILRD_RD8586_REACTOR_HPP */