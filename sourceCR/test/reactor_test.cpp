////////////////////////////////////////////////////////////////////////////////
// File Name: reactor_mark2_test.cpp                                          //
// Author: Lior Cohen                                                         //
// Date 15/07/2020                                                            //
// Purpose: test file for the subject-observer assignment                     //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "reactor.hpp"
#include "listner.hpp"
#include "source_callback.hpp"
#include "scheduler.hpp"

using namespace std;

void test(int a)
{
    a = a;
    char buff[80];
    bzero(buff, 80);
    read(0, buff, sizeof(buff));

    if (strcmp(buff, "ping\n") == 0)
    {
        write(1, "Pong\n", 5);
    }
}

class StdinHandler
{
public:
    StdinHandler(Reactor &reactor) : m_reactor(reactor) {}
    
    void Add(Handle handle, MODE mode)
    {
        Callback<Source<int> >::CallbackPointer callback(
            boost::bind(&StdinHandler::operator(), this, _1));

        b.BindCallbacks(callback);
        m_reactor.Add(handle, mode, &b);
    }

    void Run() { m_reactor.Run(); }

    void operator()(int i)
    {
        i = i;
        static int a = 0;

        if (a < 10)
        {
            test(1);

            if (a > 5)
            {
                m_reactor.Remove(0, READ);
                m_reactor.Stop();
            }
        }
        else
        {
            m_reactor.Stop();
        }

        ++a;
    }

    HandleCallback b;

private:
    Reactor &m_reactor;
};

void PrintS(int n)
{
    n = n;
    std::cout << "save me" << std::endl;
}

void PrintS1(int n)
{
    n = n;
    std::cout << "save me please" << std::endl;
}

int main()
{

    DerievedListener main_listner;
    Reactor main_reactor(&main_listner);

    Scheduler main_scheduler(main_reactor);
    boost::chrono::microseconds time(5000000);
    main_scheduler.ScheduleAction(time, &PrintS);

    boost::chrono::microseconds time1(2000000);
    main_scheduler.ScheduleAction(time1, &PrintS1);

    //main_reactor.Run();
    
    StdinHandler test(main_reactor);
    test.Add(0, READ);
    test.Run();

    return (0);
}