////////////////////////////////////////////////////////////////////////////////
// File Name: logger.hpp                                                      //
// Author: Lior Cohen                                                         //
// Date 18/08/2020                                                            //
// Purpose: header file for the logger class                                  //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef __ILRD_RD8586_LOGGER_HPP__
#define __ILRD_RD8586_LOGGER_HPP__

#include <string>
#include <boost/chrono.hpp>

#include "singleton.hpp"
#include "waitable_queue.hpp"
#include "priority_queue.hpp"

namespace ilrd
{

class Logger
{
public:
    enum ErrorLevel 
    {
        ERROR = 0,
        WARNING,
        INFO,
        DEBUG
    };
    void PushMessage(ErrorLevel error_level, std::string new_message); // construct the message and push into the queue
    
private:

    struct Message
    {
        Message(ErrorLevel error_level = ERROR, std::string new_message = "Default"); // constructor computes time here

        inline bool operator>(const Message& other_) const
        {
            return (m_timepoint > other_.m_timepoint);
        }

        //inline Message& operator=(const Message& other)

        ErrorLevel m_error_level;
        std::string m_string;
        boost::chrono::system_clock::time_point m_timepoint;
    };

    friend class Singleton<Logger>;

    //thread which will take care of it 
    void PrintMessageIntoLogfile(); // print the message in the logfile with error level and timepoint
    Logger(); 
    ~Logger();

    WaitableQueue<PriorityQueue<Message, std::vector<Message>, std::greater<Message> > , Message> m_wqueue;
    char *m_filename;
    boost::thread m_thread; // to set up in the constructor to run PrintMessageIntoLogfile
};

#define LOG_ERROR(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::ERROR, (msg)))
#define LOG_WARNING(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::WARNING, (msg)))
#define LOG_INFO(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::INFO, (msg)))
#define LOG_DEBUG(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::DEBUG, (msg)))
}

#endif /* __ILRD_RD8586_LOGGER_HPP__ */