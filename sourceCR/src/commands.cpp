////////////////////////////////////////////////////////////////////////////////
// File Name: command.cpp                                                     //
// Author: Lior Cohen                                                         //
// Date 19/08/2020                                                            //
// Purpose: functions file for the command class                              //
// Code Reviewer:                                                             //
////////////////////////////////////////////////////////////////////////////////

#include "commands.hpp"

using namespace ilrd;

WriteCommand::WriteCommand(CommandParams params) : m_params(params)
{
}

void WriteCommand::operator()()
{
    m_params.m_storage.Write(m_params.m_request.m_index,
                             (void*)&(m_params.m_request.m_data));
}

ReadCommand::ReadCommand(CommandParams params) : m_params(params)
{
}

void ReadCommand::operator()()
{
    m_params.m_storage.Read(m_params.m_request.m_index,
                            m_params.m_response.m_data);
}

CommandInterface* ilrd::WriteBuilder(CommandParams params)
{
    return (new WriteCommand(params));
}

CommandInterface* ilrd::ReadBuilder(CommandParams params)
{
    return (new ReadCommand(params));
}
