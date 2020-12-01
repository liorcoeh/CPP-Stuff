////////////////////////////////////////////////////////////////////////////////
// File Name: udp_connector.hpp                                               //
// Author: Lior Cohen                                                         //
// Date 05/08/2020                                                            //
// Purpose: header file for the udp_connector class                           //
// Code Reviewer: Ivanna Fleisher                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_UDP_CONNECTOR_HPP
#define ILRD_RD8586_UDP_CONNECTOR_HPP

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <netinet/in.h>          // struct sockaddr_in

namespace ilrd
{

class UDPConnector
{
public:
    explicit UDPConnector(int port);
    ~UDPConnector()
    {
        close (m_socket_fd);
    }

    typedef unsigned char ip_t;
    struct Address
    {
        in_addr_t m_address;
        in_port_t m_port;
    };

    void Write(const void* buffer, size_t bufffer_size,
               const Address& clientAddress);
    void Read(void* buffer, size_t bufffer_size, Address* clientAddress);

    int GetFD() const
    {
        return (m_socket_fd);
    }

private:
    int m_socket_fd;
    
};

} // namespace ilrd

#endif // ILRD_RD8586_UDP_CONNECTOR_HPP  