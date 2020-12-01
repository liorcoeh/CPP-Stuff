////////////////////////////////////////////////////////////////////////////////
// File Name: dl_loader.hpp                                                   //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: header file for the dl_loader class                               //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_DL_LOADER_HPP
#define ILRD_RD8586_DL_LOADER_HPP

#include <string>

#include "shared_object.hpp"
#include "dir_monitor.hpp"

namespace ilrd
{


class DLLoader
{
public:
    explicit DLLoader(std::string &plug_in_path);
    

    ~DLLoader();
    
private:
    void AddSharedObj(const std::string lib_name);
    
    std::string m_plug_in_path;
    Callback<Dispatcher <std::string> > m_callback;
    DirMonitor m_dir_monitor;
    std::list<SharedObject *> m_libs;
};

} // namespace ilrd

#endif // ILRD_RD8586_DL_LOADER_HPP