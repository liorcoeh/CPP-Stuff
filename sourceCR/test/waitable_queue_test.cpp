

#include <boost/thread.hpp>
#include <cassert>
#include <iostream>
#include <queue>

#include "singleton.hpp"
#include "priority_queue.hpp"
#include "waitable_queue.hpp"

using namespace std;
using namespace ilrd;

typedef Singleton<WaitableQueue<PriorityQueue<int>, int>> main_queue;

void AdvancedTests();

int main()
{
    system("clear");

    WaitableQueue<PriorityQueue<int>, int> main_queue;

    for (int i = 0; i < 5; ++i)
    {
        main_queue.Push(i + 1);
    }

    int check = 0;
    for (int i = 0; i < 5; ++i)
    {
        main_queue.Pop(check);
        cout << check << endl;
    }

    AdvancedTests();

    return (0);
}

void Producer()
{
    while (1)
    {
        int input = 0;
        cin >> input;
        main_queue::GetInstance()->Push(input);
    }
}
void Consumer()
{
    int counter = 5;
    while (counter)
    {
        int val = 0;
        WaitableQueue<PriorityQueue<int>, int>::Millisec millisec(2000);
        if (main_queue::GetInstance()->Pop(val, millisec) == 0)
        {
            cout << "value out from the queue: " << val << endl;
        }
        else
        {
            cout << "no value to input!" << endl;
        }

        --counter;
    }
}

void AdvancedTests()
{
    cout << "I am main thread" << endl;

    boost::thread prodThread(Producer);

    const int NUM_OF_CONSUMERS = 1;
    boost::thread consThread[NUM_OF_CONSUMERS];

    for (int i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        consThread[i] = boost::thread(Consumer);
    }

    prodThread.join();
    for (int i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        consThread[i].join();
    }
    // main_queue::GetInstance()->Push()
}