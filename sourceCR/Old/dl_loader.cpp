////////////////////////////////////////////////////////////////////////////////
// File Name: dl_loader.cpp                                                   //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: functions file for the dl_loader class                            //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#include <dlfcn.h>
#include <sys/inotify.h>

#include "dl_loader.hpp"
#include "logger.hpp"

using namespace ilrd;

DLLoader::DLLoader(std::string &plug_in_path) :
m_plug_in_path(plug_in_path), m_callback(boost::bind(&ilrd::DLLoader::AddSharedObj, this, _1)), m_dir_monitor(plug_in_path)
{
    m_dir_monitor.Subscribe(&m_callback);
    m_dir_monitor.StartMonitoring();
}

DLLoader:: ~DLLoader()
{}

void DLLoader::AddSharedObj(const std::string lib_name)
{
    SharedObject *new_shared_object = new SharedObject(lib_name);
    m_libs.push_front(new_shared_object);
    //delete new_shared_object;
}