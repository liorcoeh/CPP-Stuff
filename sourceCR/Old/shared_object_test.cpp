////////////////////////////////////////////////////////////////////////////////
// File Name: shared_object_test.cpp                                          //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: test file for the shared_object class                             //
// Code Reviewer:                                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>

#include "shared_object.hpp"


using namespace ilrd;

int main()
{
    system("clear");

    std::cout << "\n\nShared Object Main Test" << std::endl;
    std::cout << "-----------------------" << std::endl;

    SharedObject main_object("/home/liorcoeh/git/lior-cohen/cpp/sourceCR/check/libfoo.so");

    void (*fun_ptr)(void);

    *(void**)(&fun_ptr) = main_object.LoadSymbol<void (*)()>("_Z3foov");

    fun_ptr();

    return (0);
}