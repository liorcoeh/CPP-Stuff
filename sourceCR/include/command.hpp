////////////////////////////////////////////////////////////////////////////////
// File Name: command.hpp                                                     //
// Author: Lior Cohen                                                         //
// Date 12/07/2020                                                            //
// Purpose: header file for the command class                                 //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_COMMAND_HPP
#define ILRD_RD8586_COMMAND_HPP

namespace ilrd
{

class CommandInterface
{
public:
    virtual void operator()() = 0;
    virtual ~CommandInterface() = 0;
};

inline CommandInterface::~CommandInterface()
{
}

} // namespace ilrd

#endif /* ILRD_RD8586_COMMAND_HPP */
