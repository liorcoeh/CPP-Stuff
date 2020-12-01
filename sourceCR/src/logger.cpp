////////////////////////////////////////////////////////////////////////////////
// File Name: logger.cpp                                                      //
// Author: Lior Cohen                                                         //
// Date 18/08/2020                                                            //
// Purpose: functions file for the logger class                               //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <fstream>
#include <time.h>

#include "logger.hpp"

using namespace ilrd;

Logger::Message::Message(ErrorLevel error_level, std::string message):
    m_error_level(error_level), m_string(message), m_timepoint(boost::chrono::system_clock::now())
{
}

Logger::Logger():m_filename(getenv("LOGGERNAME"))
{
    m_thread = boost::thread(boost::bind(&Logger::PrintMessageIntoLogfile, this));
    std::fstream fs;
    fs.open("logger.txt", ios::app);
    fs.close();
}

Logger::~Logger()
{   
    while (!m_wqueue.Empty())
    {
        ;
    }

    m_thread.interrupt();
    m_thread.join();
}

void Logger::PushMessage(ErrorLevel error_level, std::string new_message)
{
    Message message(error_level, new_message);
    m_wqueue.Push(message);
}

void Logger::PrintMessageIntoLogfile()
{
    Logger::Message message(ERROR, "Default");
    string total_message;
    while (1)
    {
        sleep(1);
        m_wqueue.Pop(message);

        std::time_t t = boost::chrono::system_clock::to_time_t(message.m_timepoint);
        total_message = std::ctime(&t);

        total_message += "Log Type - " + boost::to_string(message.m_error_level) + "\nMessage: " + message.m_string + "\n\n"; 
        std::fstream fs;

        fs.open("logger.txt", std::fstream::app);
        fs.write(total_message.c_str(), total_message.length());
        fs.close();
    }
}
