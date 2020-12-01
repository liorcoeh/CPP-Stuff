////////////////////////////////////////////////////////////////////////////////
// File Name: dir_monitor.cpp                                                 //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: functions file for the dir_monitor class                          //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#include <dlfcn.h>
#include <sys/inotify.h>
#include <boost/thread.hpp>

#include "dir_monitor.hpp"
#include "logger.hpp"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

using namespace ilrd;

DirMonitor::DirMonitor(std::string dir_path) : m_path(dir_path), m_run(true)
{}

DirMonitor::~DirMonitor()
{
    m_run = false;
}

void DirMonitor::Subscribe(Callback<Dispatcher<std::string>> *callback)
{
    m_dispatcher.Subscribe(callback);
}

void DirMonitor::UnSubscribe(Callback<Dispatcher<std::string>> *callback)
{
    m_dispatcher.Unsubscribe(callback);
}

//void DirMonitor::Running()
void DirMonitor::Running()
{
    int fd = inotify_init();

    if (0 > fd)
    {
        //LOG_ERROR("Failed to inotify in dir_monitor.cpp");
        std::cout << "Failed to inotify in dir_monitor.cpp" << std::endl;
    }

    int wd = inotify_add_watch(fd, m_path.c_str(), IN_CREATE | IN_CLOSE_WRITE | IN_DELETE);

    if (0 > wd)
    {
        //LOG_ERROR("Failed to inotify_add_watch in dir_monitor.cpp");
        std::cout << "Failed to inotify_add_watch in dir_monitor.cpp" << std::endl;
    }
    else
    {
        std::cout << "Watching:" << m_path.c_str() << std::endl; 
    }

    char buffer[EVENT_BUF_LEN];
    int length = read(fd, buffer, EVENT_BUF_LEN);

    if (0 > length)
    {
        //LOG_ERROR("Failed to read in dir_monitor.cpp");
        std::cout << "Failed to read in dir_monitor.cpp" << std::endl;
    }

    int i = 0;

    while (m_run)
    {
        i = 0;

        length = read(fd, buffer, EVENT_BUF_LEN);  

        if (length < 0)
        {
            //LOG_ERROR("Failed to read in dir_monitor");
        }  

        while (i < length)
        { 
            
            struct inotify_event *event = (struct inotify_event*) &buffer[i];
            if (event->len)
            {
                if (event->mask & IN_CREATE)
                {
                    if (event->mask & IN_ISDIR)
                    {
                        //LOG_INFO("The directory %s was created\n", event->name);
                        std::cout << "The directory " << event->name << 
                        " was created" << std::endl;
                        m_dispatcher.Notify(&event->name[0]);
                    }

                    else
                    {
                        //LOG_INFO("The file %s was created with wd: %d\n", event->name, name->wd);
                        std::cout << "The file " << event->name << 
                        " was created with " << event->wd << std::endl;
                        m_dispatcher.Notify(&event->name[0]);
                    }     
                }
            
                else if (event->mask & IN_CLOSE_WRITE)
                {
                    if (event->mask & IN_ISDIR)
                    {
                        //LOG_INFO("The directory %s was modified\n", event->name);
                        std::cout << "The directory " << event->name << 
                        " was modified" << std::endl;
                        m_dispatcher.Notify(&event->name[0]);
                    }       
                    else
                    {
                        //LOG_INFO("The file %s was modified with wd: %d\n", event->name, name->wd);
                        std::cout << "The file " << event->name << 
                        " was modified with " << event->wd << std::endl;
                        m_dispatcher.Notify(&event->name[0]);
                    }    
                }
            
                else if (event->mask & IN_DELETE)
                {
                    if (event->mask & IN_ISDIR)
                    {
                        //LOG_INFO("The file %s was deleted\n", event->name);
                        std::cout << "The director " << event->name << 
                        " was deleted" << std::endl;
                        m_dispatcher.Notify(&event->name[0]);
                    }     
                    else
                    {
                        //LOG_INFO("The file %s was deleted with wd: %d\n", event->name, name->wd);
                        std::cout << "The file " << event->name << 
                        " was deleted with wd " << event->wd << std::endl;
                        m_dispatcher.Notify(&event->name[0]);
                    }      
                }
                
                i += EVENT_SIZE + event->len;           
            }
        }
    }

    inotify_rm_watch(fd, wd);

    close(fd);
}

void DirMonitor::StartMonitoring()
{
    boost::thread thread{&DirMonitor::Running, this};
}

