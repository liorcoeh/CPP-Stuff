////////////////////////////////////////////////////////////////////////////////
// File Name: master_communicator.cpp                                         //
// Author: Lior Cohen                                                         //
// Date 09/08/2020                                                            //
// Purpose: functions file for the master_communicator class                  //
// Code Reviewer: Ivanna Fleisher                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <boost/bind.hpp>
extern "C"
{
#include <sys/socket.h> // socket
}

#include "minion_protocol.hpp"
#include "master_communicator.hpp"

using namespace ilrd;

MasterCommunicator::MasterCommunicator(int port, Reactor& reactor,
    ActionRequest ar_func) :
            m_arFunc(ar_func), m_udpConnector(port), m_reactor(reactor),
            m_callback(boost::bind(&MasterCommunicator::ReadRequest, this, _1))
{
    memset(&m_clientAddress, 0, sizeof(UDPConnector::Address));

    m_reactor.Add(m_udpConnector.GetFD(), detail::READ, &m_callback);
}

MasterCommunicator::~MasterCommunicator()
{
    m_reactor.Remove(GetFD(), detail::READ, &m_callback);
}

void MasterCommunicator::ReadRequest(int fd)
{
    (void)fd;
    Request* request =
        static_cast< Request* >(operator new(NET_BUFFSIZE(Request)));
    memset(request, 0, NET_BUFFSIZE(Request));

    m_udpConnector.Read((void*)request, NET_BUFFSIZE(Request),
                        &m_clientAddress);

    request->m_index = NtoH(request->m_index);

    m_arFunc(*request);
    operator delete(request);
}

void MasterCommunicator::Reply(const Response& res)
{
    size_t messageSize = (res.m_mode == 1) ? offsetof(Response, m_data[0])
                                           : NET_BUFFSIZE(Response);

    m_udpConnector.Write((void*)&res, messageSize, m_clientAddress);
}


