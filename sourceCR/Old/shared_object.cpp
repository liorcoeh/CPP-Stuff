////////////////////////////////////////////////////////////////////////////////
// File Name: shared_object.cpp                                               //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: functions file for the shared_object class                        //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////



#include "shared_object.hpp"

using namespace ilrd;

SharedObject::SharedObject(const std::string& library_path):
               m_path(library_path)
{
    m_handle = dlopen(m_path.c_str(), RTLD_LAZY);
}

SharedObject::~SharedObject()
{
    dlclose(m_handle);
}

//template <typename T>
// void* SharedObject::LoadSymbol(std::string symbol)
// {
//     return (dlsym(m_handle, symbol.c_str()));
// }