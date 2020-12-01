

#ifndef ILRD_RD8586_UDP_CONNECTOR_DETAIL_HPP
#define ILRD_RD8586_UDP_CONNECTOR_DETAIL_HPP

#include <iostream>     // runtime_error
#include <netinet/in.h> // struct sockaddr_in
#include <string>
#include <sys/socket.h> // socket

namespace ilrd
{

namespace detail
{

inline static struct sockaddr_in GetSockaddr(int port)
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);

    return (server_addr);
}

inline int SetupUDPListener(int port)
{
    int server_socket = 0;
    struct sockaddr_in server_addr = GetSockaddr(port);

    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        throw std::runtime_error("can't create socket");
    }

    if (bind(server_socket, (struct sockaddr*)&server_addr,
             sizeof(server_addr)) == -1)
    {
        throw std::runtime_error("can't bind socket");
    }

    return (server_socket);
}

} // namespace detail

} // namespace ilrd

#endif /* ILRD_RD8586_UDP_CONNECTOR_DETAIL_HPP */