////////////////////////////////////////////////////////////////////////////////
// File Name: udp_connector.cpp                                               //
// Author: Lior Cohen                                                         //
// Date 05/08/2020                                                            //
// Purpose: functions file for the udp_connector class                        //
// Code Reviewer: Ivanna Fleisher                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <string.h>

#include "udp_connector.hpp"
#include "udp_connector_detail.hpp" // SetupUDPListener

using namespace ilrd;
using namespace detail;

UDPConnector::UDPConnector(int port) : m_socket_fd(SetupUDPListener(port))
{}

void UDPConnector::Read(void* buffer, size_t bufffer_size,
                        Address* clientAddress)
{
    sockaddr_storage clientAddr;
    socklen_t len;

    bzero(&clientAddr, sizeof(clientAddr));
    len = sizeof(clientAddr);

    int bytes_received = recvfrom(m_socket_fd, buffer, bufffer_size, 0,
                                  (struct sockaddr*)&clientAddr, &len);

    if (bytes_received < 0)
    {
        throw std::runtime_error(strerror(errno));
    }

    sockaddr_in* ip4 = (sockaddr_in*)&clientAddr;

    clientAddress->m_address = ip4->sin_addr.s_addr;
    clientAddress->m_port = ip4->sin_port;
}

void UDPConnector::Write(const void* buffer, size_t bufffer_size,
                         const Address& clientAddress)
{
    sockaddr_in address;
    bzero(&address, sizeof(sockaddr_in));

    address.sin_family = AF_INET;
    address.sin_port = clientAddress.m_port;
    address.sin_addr.s_addr = clientAddress.m_address;

    if (0 > sendto(m_socket_fd, buffer, bufffer_size, 0,
                   (const struct sockaddr*)&address, sizeof(sockaddr)))
    {
        throw std::runtime_error(strerror(errno));
    }
}


