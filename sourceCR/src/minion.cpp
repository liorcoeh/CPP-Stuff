////////////////////////////////////////////////////////////////////////////////
// File Name: minion.cpp                                                      //
// Author: Lior Cohen                                                         //
// Date 09/08/2020                                                            //
// Purpose: functions file for the minion class                               //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#include <boost/bind.hpp> // boost::bind
#include <cassert>        // assert
#include <iostream>       // cout, runtime_error
#include <string>         // to_string

#include "commands.hpp"
#include "minion.hpp"           // Minion class
#include "reactor_listener.hpp" // ReactorListener class

using namespace ilrd;

Minion::Minion(int port, int num_of_blocks, int master_port)
    : m_reactor(new ReactorListener),
      m_comm(port, m_reactor, boost::bind(&Minion::OnRequest, this, _1)),
      m_storage(num_of_blocks)
{
    LOG_INFO("Minion::Ctor");

    CommandFactory->Add(0, ReadBuilder);
    CommandFactory->Add(1, WriteBuilder);

    (void)master_port;
}

Minion::~Minion()
{
    LOG_INFO("Minion::Dtor");
    m_reactor.Stop();
}

void Minion::Run()
{
    LOG_INFO("Minion::Run");
    m_reactor.Run();
}

void Minion::OnRequest(const Request& request)
{
    assert(request.m_mode == 0 || request.m_mode == 1);

    std::ostringstream log;
    log << "Minion::OnRequest: request received, "
        << (request.m_mode == 0 ? "read" : "write") << " mode, index "
        << request.m_index;
    LOG_INFO(log.str());

    size_t responseSize =
        offsetof(Response, m_data[0]) + (1 - request.m_mode) * MAX_DATA_SIZE;
    Response* response = NULL;

    try
    {
        response = (Response*)operator new(responseSize);
        memset(response, 0, responseSize);

        CommandInterface* command = CommandFactory->Create(
            request.m_mode, CommandParams(m_storage, *response, request));

        (*command)();
        response->m_status = 0;
        delete command;
    }
    catch (...)
    {
        if (response)
        {
            operator delete(response);
        }

        LOG_ERROR("Minion::OnRequest: error while creating response");
        response->m_status = -1;
    }

    response->m_mode = request.m_mode;
    response->m_uid = request.m_uid;

    m_comm.Reply(*response);

    LOG_INFO("Minion::OnRequest: response message sent");

    operator delete(response);
}