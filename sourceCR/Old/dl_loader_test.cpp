////////////////////////////////////////////////////////////////////////////////
// File Name: ld_loader_test.cpp                                              //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: test file for the ld_loader class                                 //
// Code Reviewer:                                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <string>

#include "callback.hpp"
#include "dir_monitor.hpp"
#include "dl_loader.hpp"

using namespace ilrd;

int main()
{
    system("clear");

    std::cout << "\n\nMain ld_loader test" << "\n-----------------\n\n" << std::endl;

    std::string plug_in_path("/home/liorcoeh/git/lior-cohen/cpp/sourceCR/check");

    DLLoader main_loader(plug_in_path);

    sleep(30);

    std::cout << "Closing the program\n" << std::endl;

    return (0);
}