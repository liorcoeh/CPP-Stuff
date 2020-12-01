////////////////////////////////////////////////////////////////////////////////
// File Name: priority_queue.hpp                                              //
// Author: Lior Cohen                                                         //
// Date 04/09/2020                                                            //
// Purpose: header file for the priority_queue class                          //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_PRIORITYQUEUE_HPP
#define ILRD_RD8586_PRIORITYQUEUE_HPP

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

namespace ilrd
{

template <typename T, typename Container = std::vector<T>,
  typename Compare = std::less<typename Container::value_type>>
class PriorityQueue : private std::priority_queue<T, Container, Compare>
{
public:
    explicit PriorityQueue(const Compare& comp = Compare(),
                         const Container& ctnr = Container());
                         
    /*template <class InputIterator>
    PriorityQueue(InputIterator first, InputIterator last,
                         const Compare& comp = Compare(),
                         const Container& ctnr = Container());*/ //not mandatory (bonus)
    void push (const T& val);
    void pop();
    const T& front() const;
    bool empty() const;
 
};

template < typename T, class Container, class Compare >
PriorityQueue< T, Container, Compare >::PriorityQueue(const Compare& comp,
                                                      const Container& ctnr)
    : PriorityQueue::priority_queue(comp, ctnr)
{}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::push(const T& value)
{
    priority_queue<T, Container, Compare>::push(value);
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::pop()
{
    priority_queue<T, Container, Compare>::pop();
}

template <typename T, typename Container, typename Compare>
const T& PriorityQueue<T, Container, Compare>::front() const
{
    return (priority_queue<T, Container, Compare>::top());
}

template <typename T, typename Container, typename Compare>
bool PriorityQueue<T, Container, Compare>::empty() const
{
    return (priority_queue<T, Container, Compare>::empty());
}

} // namespce ilrd

#endif // ILRD_RD8586_PRIORITYQUEUE_HPP