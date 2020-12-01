////////////////////////////////////////////////////////////////////////////////
// File Name: commands.hpp                                                    //
// Author: Lior Cohen                                                         //
// Date 20/08/2020                                                            //
// Purpose: header file for the commands class                                //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_COMMANDS_HPP
#define ILRD_RD8586_COMMANDS_HPP

#include "command.hpp"         // CommandInterface class
#include "minion_protocol.hpp" // minion protocols and defines
#include "storage.hpp"         // Storage class

namespace ilrd
{
struct CommandParams
{
public:
    CommandParams(Storage< MAX_DATA_SIZE >& storage, Response& res,
                  const Request& req)
        : m_storage(storage), m_response(res), m_request(req)
    {
    }

    Storage< MAX_DATA_SIZE >& m_storage;
    Response& m_response;
    const Request& m_request;
};

// Factory< std::string, CommandInterface, CommandParams< BLOCKSIZE > >

class WriteCommand : public CommandInterface
{
public:
    WriteCommand(CommandParams params);
    void operator()();

private:
    CommandParams m_params;
};

class ReadCommand : public CommandInterface
{
public:
    ReadCommand(CommandParams params);
    void operator()();

private:
    CommandParams m_params;
};

// BUILDERS
CommandInterface* WriteBuilder(CommandParams params);

CommandInterface* ReadBuilder(CommandParams params);

} // namespace ilrd

#endif // ILRD_RD8586_COMMANDS_HPP