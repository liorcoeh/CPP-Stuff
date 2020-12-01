////////////////////////////////////////////////////////////////////////////////
// File Name: singleton_test.cpp                                              //
// Author: Lior Cohen                                                         //
// Date 29/07/2020                                                            //
// Purpose: test file for the singleton                                       //
// Code Reviewer: Amir Saraf                                                  //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include "singleton.hpp"

using namespace std;

#define NUM_THREADS (5)

class Logger : private boost::noncopyable
{
public:
    Logger() {};
    ~Logger() {};

    bool OpenLogFile(string file_name);
    void WriteToLogFile(const string& content);
    bool CloseLogFile(string file_name);

private:
    ofstream m_file_name;
    boost::mutex m_lock;
};

bool Logger::OpenLogFile(string file_name)
{
    m_lock.lock();
    m_file_name.open(file_name,  std::fstream::app);
    m_lock.unlock();
}

void Logger::WriteToLogFile(const string& content)
{
    m_lock.lock();
    m_file_name << content << endl;
    m_lock.unlock();
}

bool Logger::CloseLogFile(string file_name)
{
    m_lock.lock();
    m_file_name.close();
    m_lock.unlock();
}

void *ThreadFunc(void *arg)
{
    (void)arg;
    Logger *log = Singleton<Logger>::GetInstance();

    log->OpenLogFile("myfile.txt");
    log->WriteToLogFile("Lior");
    log->CloseLogFile("myfile.txt");
}

// g++ singleton_test.cpp -lboost_thread -lboost_system -lpthread

int main()
{
    system("clear");

    pthread_t threads[NUM_THREADS];
    cout << "\nmain\n" << endl;

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, ThreadFunc, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    Singleton<Logger>::CleanUp();

    cout << "Exiting main" << endl;

    return (0);
}