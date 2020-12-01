////////////////////////////////////////////////////////////////////////////////
// File Name: thread_pool.cpp                                                 //
// Author: Lior Cohen                                                         //
// Date 04/09/2020                                                            //
// Purpose: functions file for the thread_pool class                          //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#include "thread_pool.hpp"

#define WAIT_TIME (50)

ilrd::ThreadPool::Task::~Task()
{}

void ilrd::ThreadPool::Task::operator()()
{
    m_exec_func(0);
}

ilrd::ThreadPool::ThreadPool(size_t num_of_threads) : m_total_num(num_of_threads),
m_paused(false), m_run(true)
{
    for (size_t i = 0; i < m_total_num; ++i)
    {

        m_threads.push_back(shrd_ptr_thread(new boost::thread(boost::bind(&ThreadPool::ThreadLoop, this))));
    }
}

void ilrd::ThreadPool::AddTask(const Task &task)
{
    m_tasks.Push(task);
}

bool ilrd::ThreadPool::SetThreadsAmount(size_t new_amount)
{
    Stop();
    m_total_num = new_amount;
    m_run = true;

    for (size_t i = 0; i < m_total_num; ++i)
    {
        m_threads.push_back(shrd_ptr_thread(new boost::thread(boost::bind(&ThreadPool::ThreadLoop, this))));
    }

    return 1;
}

void ilrd::ThreadPool::Stop()
{
    m_run = false;
    m_cond.notify_all();

    for (size_t i = 0; i < m_total_num; ++i)
    {
        m_threads[i]->join();
    }
}

void ilrd::ThreadPool::Pause()
{
    m_paused = true;
}

void ilrd::ThreadPool::Resume()
{

    m_paused = false;
    m_cond.notify_all();
}

void ilrd::ThreadPool::ThreadLoop()
{

    while (m_run)
    {
        while (m_paused)
        {
            boost::unique_lock<boost::mutex> lock(m_pause_mutex);
            m_cond.wait(lock);
        }

        Task task(boost::bind(&ThreadPool::EMPTYFUNC, this, _1));
        m_tasks.Pop(task, WaitableQueue<std::queue<Task>, Task>::Millisec(WAIT_TIME));
        task();
    }
}