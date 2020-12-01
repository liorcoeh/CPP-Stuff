////////////////////////////////////////////////////////////////////////////////
// File Name: master_communicator.hpp                                         //
// Author: Lior Cohen                                                         //
// Date 09/08/2020                                                            //
// Purpose: header file for the master_communicator class                     //
//          Takes the information from the MASTER and sends it to the minion  //
//          and receives responds from the minion to the MASTER               //
// Code Reviewer: Ivanna Fleisher                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__
#define __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable

#include "udp_connector.hpp"
#include "reactor.hpp"
#include "minion_protocol.hpp"

namespace ilrd
{

class MasterCommunicator : private boost::noncopyable
{
public:
    typedef boost::function< void(const Request&) > ActionRequest;

    explicit MasterCommunicator(int port, Reactor& reactor,
                                ActionRequest ar_func);

    ~MasterCommunicator();

    // ReadRequest Function (added to reactor)
    // Receives: file descriptor.
    // Returns: nothing
    void ReadRequest(int fd);

    // Reply Function
    // Receives: const refernce to class Response.
    // Returns: nothing
    void Reply(const Response& res);

    int GetFD()
    {
        return (m_udpConnector.GetFD());
    }

private:
    UDPConnector::Address m_clientAddress;
    ActionRequest m_arFunc;
    UDPConnector m_udpConnector;
    Reactor& m_reactor;
    Callback<Dispatcher<int>> m_callback;
};

} // namespace ilrd

#endif /* __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__ */