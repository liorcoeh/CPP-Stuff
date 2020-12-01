////////////////////////////////////////////////////////////////////////////////
// File Name: thread_pool.hpp                                                 //
// Author: Lior Cohen                                                         //
// Date 04/09/2020                                                            //
// Purpose: header file for the thread_pool class                             //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_THREAD_POOL_HPP
#define ILRD_RD8586_THREAD_POOL_HPP

#include <vector>
#include <queue>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

#include "waitable_queue.hpp"

namespace ilrd
{

    typedef boost::shared_ptr<boost::thread> shrd_ptr_thread;

    class ThreadPool : private boost::noncopyable
    {
    public:
        typedef boost::function<void(int)> ActionFunc;
        class Task
        {
        public:
            Task(ActionFunc func) : m_exec_func(func) {}
            Task &operator=(Task &other)
            {
                this->m_exec_func = other.m_exec_func;
                return *this;
            }
            virtual ~Task();
            virtual void operator()();

        private:
            ActionFunc m_exec_func;
        };

        explicit ThreadPool(size_t num_of_threads);
        ~ThreadPool() { Stop(); }
        void AddTask(const Task &task);
        bool SetThreadsAmount(size_t new_amount); //Set a new amount of threads
        void Stop();                              //Exits all threads
        void Pause();                             //Pause all threads
        void Resume();                            //Resume all threads to work again

    private:
        void ThreadLoop();
        void EMPTYFUNC(int x = 0)
        {
            (void)x;
        }

        size_t m_total_num;
        std::vector<shrd_ptr_thread> m_threads;
        WaitableQueue<std::queue<Task>, Task> m_tasks;

        boost::condition_variable m_cond;
        boost::mutex m_pause_mutex;
        bool m_paused;
        bool m_run;
    };

} // namespace ilrd

#endif // ILRD_RD8586_THREAD_POOL_HPP