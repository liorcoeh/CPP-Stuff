////////////////////////////////////////////////////////////////////////////////
// File Name: udp_connector.cpp                                               //
// Author: Lior Cohen                                                         //
// Date 03/08/2020                                                            //
// Purpose: test file for the udp_connector class                             //
// Code Reviewer: Ivanna Fleisher                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string.h>

#include "udp_connector.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    UDPConnector udp(8080);

    socklen_t length;
    int bytes_received;
    char buffer[100]; 
    char message[] = "pong";
    struct sockaddr_in server_addr;

    system("clear");

    std::cout << "socket = " << udp.GetFD() << std::endl;

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(8080);

    while(1)
    {
        sendto(udp.GetFD(), (const char *)message, strlen(message),  
            MSG_CONFIRM, (const struct sockaddr *) &server_addr, 
                sizeof(server_addr));  
    
        bytes_received = recvfrom(udp.GetFD(), (char *)buffer, 100,  
                    MSG_WAITALL, ( struct sockaddr *) &server_addr, 
                    &length); 
        buffer[bytes_received] = '\0'; 
        std::cout << "Server: " << buffer << std::endl;
    }
    
    return 0;
}