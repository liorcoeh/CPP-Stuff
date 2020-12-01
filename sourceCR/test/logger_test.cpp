////////////////////////////////////////////////////////////////////////////////
// File Name: logger.hpp                                                      //
// Author: Lior Cohen                                                         //
// Date 18/08/2020                                                            //
// Purpose: test file for the logger class                                    //
// Code Reviewer: Kobi Rappaport                                              //
////////////////////////////////////////////////////////////////////////////////

#include "logger.hpp"
#include "singleton.hpp"

using namespace ilrd;

int main()
{
    LOG_DEBUG("Debug Error");
    Singleton<Logger>::CleanUp();

    return (0);
}