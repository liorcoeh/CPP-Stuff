////////////////////////////////////////////////////////////////////////////////
// File Name: dir_monitor_test.cpp                                            //
// Author: Lior Cohen                                                         //
// Date 30/08/2020                                                            //
// Purpose: test file for the dir_monitor class                               //
// Code Reviewer:                                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>

#include "callback.hpp"
#include "dir_monitor.hpp"

using namespace ilrd;

void FirstPrint(std::string str);
void SecondPrint(std::string str);

int main()
{
    system("clear");

    std::cout << "\n\nMain dir_monitor test" << std::endl;
    std::cout << "---------------------\n\n" << std::endl;

    DirMonitor main_monitor("/home/liorcoeh/git/lior-cohen/cpp/sourceCR/lib");

    Callback<Dispatcher<std::string>> first_callback(FirstPrint);
    Callback<Dispatcher<std::string>> second_callback(SecondPrint);

    main_monitor.Subscribe(&first_callback);
    main_monitor.Subscribe(&second_callback);

    main_monitor.StartMonitoring();

    std::cout << "In main thread, during the monitoring" << std::endl;

    sleep(20);

    std::cout << "Getting out" << std::endl;

    return (0);
}

void FirstPrint(std::string str)
{
    std::cout << "From First, string is: " << str.c_str() << std::endl;
}

void SecondPrint(std::string str)
{
    std::cout << "From Second, string is: " << str.c_str() << std::endl;
}

