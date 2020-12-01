////////////////////////////////////////////////////////////////////////////////
// File Name: dir_monitor.hpp                                                 //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: header file for the dir_monitor class                             //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_IDR_MONITOR_HPP
#define ILRD_RD8586_IDR_MONITOR_HPP

#include <string>

#include "callback.hpp"
#include "dispatcher.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    explicit DirMonitor(std::string dir_path);
    ~DirMonitor();
    void Subscribe(Callback<Dispatcher<std::string> > *callback);
    void UnSubscribe(Callback<Dispatcher<std::string> > *callback);
    void StartMonitoring();

private:
    std::string m_path;
    Dispatcher<std::string> m_dispatcher;
    bool m_run;
    void Running();

};

} // namespace ilrd

#endif // ILRD_RD8586_IDR_MONITOR_HPP