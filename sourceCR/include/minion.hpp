////////////////////////////////////////////////////////////////////////////////
// File Name: minion.hpp                                                      //
// Author: Lior Cohen                                                         //
// Date 09/08/2020                                                            //
// Purpose: header file for the minion class                                  //
// Code Reviewer: Ivanna Fleisher                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef __ILRD_RD8586_MINION_HPP__
#define __ILRD_RD8586_MINION_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable

#include "minion_protocol.hpp"
#include "reactor.hpp"
#include "master_communicator.hpp"
#include "storage.hpp"
#include "commands.hpp"
#include "factory.hpp"
#include "singleton.hpp"
#include "logger.hpp"

#define CommandFactory                                                         \
    (Singleton<                                                                \
        Factory< char, CommandInterface, CommandParams > >::GetInstance())

namespace ilrd
{
class Minion : private boost::noncopyable
{
    public:
        explicit Minion(int port, int num_of_blocks, int master_port);
        ~Minion();

        // Run
        // Receives: nothing
        // Returns: nothing
        void Run();
    private:

        // OnRequest
        // Receives: Request structure.
        // Returns: nothing
        void OnRequest(const Request& request);

        Reactor m_reactor;
        MasterCommunicator m_comm;
        Storage<4096> m_storage;
    };

} // namespace ilrd

#endif /* __ILRD_RD8586_Minion_HPP__ */

