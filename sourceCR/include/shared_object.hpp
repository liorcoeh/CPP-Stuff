////////////////////////////////////////////////////////////////////////////////
// File Name: shared_object.hpp                                               //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: header file for the shared_object class                           //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_SHARED_OBJECT_HPP
#define ILRD_RD8586_SHARED_OBJECT_HPP

#include <string>
#include <dlfcn.h>

//#include "logger.hpp"

namespace ilrd
{

class SharedObject
{
public:
    explicit SharedObject(const std::string& library_path);
    ~SharedObject();

    template <typename T>
    T* LoadSymbol(std::string symbol);

private:
    std::string m_path;
    void *m_handle;
};


template <typename T>
T* SharedObject::LoadSymbol(std::string symbol)
{
    void *check = dlsym(m_handle, symbol.c_str());

    if (!check)
    {
        //LOG_ERROR("Failed dlstm in shared object");
        throw ("Failed dlsym in shared object");
    }
    return ((T*)check);
}

} // namespace ilrd

#endif // ILRD_RD8586_SHARED_OBJECT_HPP