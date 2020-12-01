////////////////////////////////////////////////////////////////////////////////
// File Name: thread_pool_test.cpp                                            //
// Author: Lior Cohen                                                         //
// Date 04/09/2020                                                            //
// Purpose: test file for the thread_pool_test class                          //
// Code Reviewer: Amir Saraf                                                  //
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // ostream

#include "thread_pool.hpp" // singleton implementation

using namespace ilrd;

static int i = 0;

void First(int x = 0)
{
    (void)x;
    std::cout << "From first i ==> " << i << std::endl;
    ++i;
    sleep(1);
}

void Second(int x = 0)
{
    (void)x;
    std::cout << "From second j ==> " << i << std::endl;
    --i;
}

int main() 
{ 
    ThreadPool pool(6);

    sleep(2);

    for (int i = 0; i < 10; ++i)
    {
        pool.AddTask(ThreadPool::Task(First));
    }

    pool.Pause();
    std::cout << "Paused\n";

    for (int i = 0; i < 10; ++i)
    {
        pool.AddTask(ThreadPool::Task(First));
    }

    sleep(2);

    std::cout << "Resuming\n";
    pool.Resume();


    sleep(2);

    pool.SetThreadsAmount(1);

    for (int i = 0; i < 10; ++i)
    {
        pool.AddTask(ThreadPool::Task(Second));
    }

    sleep(3);

    return 0;
}