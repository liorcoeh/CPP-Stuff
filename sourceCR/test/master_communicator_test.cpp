////////////////////////////////////////////////////////////////////////////////
// File Name: master_communicator_test.cpp                                    //
// Author: Lior Cohen                                                         //
// Date 09/08/2020                                                            //
// Purpose: test file for the master_communicator class                       //
// Code Reviewer: Ivanna Fleisher                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>      
#include <cstring>      
#include <arpa/inet.h>  

#include "master_communicator.hpp"
#include "storage.hpp"
#include "d_listner.hpp"
#include "reactor.hpp"

using namespace ilrd;

void ARFunc(const Request& request);

IListener *main_listner = new DerievedListener;

Reactor main_reactor(main_listner);
MasterCommunicator master_communicator(8080, main_reactor, ARFunc);

void ARFunc(const Request& request)
{
    std::cout << "ARFunc\n";
    std::cout << request.m_mode << std::endl;
    std::cout << request.m_index << std::endl;
    std::cout << request.m_uid << std::endl;
    std::cout << request.m_data << std::endl;

    size_t msg_size = Request().RequestSize();

    Response *response = (Response *)operator new (msg_size);

    bzero(response, msg_size);

    response->m_mode = '0';
    response->m_status = 'A';
    response->m_uid = 456789;
    memcpy(response->m_data, "helloback", 10);

    master_communicator.Reply(*response);
    delete response;

    main_reactor.Stop();
}

int main()
{
    main_reactor.Run();

    delete main_listner;
    
    return 0;

}

