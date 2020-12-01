

#include <iostream>

#include "priority_queue.hpp"
#include "waitable_queue.hpp"

using namespace std;
using namespace ilrd;

void PrintQueue(PriorityQueue<int> &queue);
void PrintWaitQueue(WaitableQueue<PriorityQueue<int>, int> &queue);

int main()
{
    system("clear");

    PriorityQueue<int> first_queue;

    first_queue.push(1);
    first_queue.push(3);
    first_queue.push(2);

    PrintQueue(first_queue);

    WaitableQueue<PriorityQueue<int>, int> main_queue;

    main_queue.Push(1);
    main_queue.Push(3);
    main_queue.Push(2);

    PrintWaitQueue(main_queue);

    return (0);
}

void PrintQueue(PriorityQueue<int> &queue)
{
    while (!queue.empty())
    {
        cout << queue.front() << endl;
        queue.pop();
    }
}

void PrintWaitQueue(WaitableQueue<PriorityQueue<int>, int> &queue)
{
    int value = 0;

    while (!queue.Empty())
    {
        queue.Pop(value);
        cout << value << endl;
    }
}