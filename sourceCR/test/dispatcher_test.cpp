////////////////////////////////////////////////////////////////////////////////
// File Name: dispatcher_test.hpp                                             //
// Author: Lior Cohen                                                         //
// Date 18/08/2020                                                            //
// Purpose: test file for the dispatcher class                                //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>

#include "dispatcher.hpp"
#include "callback.hpp"

using namespace ilrd;

void FirstPrint(int num);
void SecondPrint(int num);

int main()
{
    system("clear");

    Dispatcher<int> main_dispatcher;

    Callback<Dispatcher<int>> first_callback(FirstPrint);
    Callback<Dispatcher<int>> second_callback(SecondPrint);

    main_dispatcher.Subscribe(&first_callback);
    main_dispatcher.Subscribe(&second_callback);

    main_dispatcher.Notify(1);

    std::cout << std::endl;

    main_dispatcher.Unsubscribe(&first_callback);
    main_dispatcher.Notify(1);

    return (0);
}

void FirstPrint(int num)
{
    std::cout << "From First num is:" << num << std::endl;
}

void SecondPrint(int num)
{
    std::cout << "From Second num is:" << num << std::endl;
}