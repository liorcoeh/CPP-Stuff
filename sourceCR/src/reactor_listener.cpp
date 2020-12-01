

extern "C"
{
#include <sys/select.h> // select, SET_FD macros
}

#include "reactor_listener.hpp"

using namespace ilrd;
using namespace std;
using namespace detail;

ReactorListener::~ReactorListener()
{
}

vector< HandleAndMode >
ReactorListener::Listen(const vector< HandleAndMode >& handles)
{
    fd_set ReadFDs;
    fd_set WriteFDs;
    fd_set ExceptFDs;

    FD_ZERO(&ReadFDs);
    FD_ZERO(&WriteFDs);
    FD_ZERO(&ExceptFDs);

    // create FD_SETs of the right mode
    vector< HandleAndMode >::const_iterator i;
    for (i = handles.begin(); i != handles.end(); ++i)
    {
        switch (i->second)
        {
        case READ:
            FD_SET(i->first, &ReadFDs);
            break;

        case WRITE:
            FD_SET(i->first, &WriteFDs);
            break;

        case EXCEPTION:
            FD_SET(i->first, &ExceptFDs);
            break;

        default:
            break;
        }
    }

    if (select(FD_SETSIZE, &ReadFDs, &WriteFDs, &ExceptFDs, NULL) == -1)
    {
        throw domain_error("select failed");
    }

    // create the vector to return
    vector< HandleAndMode > retVector;
    for (int i = 0; i < FD_SETSIZE; ++i)
    {
        if (FD_ISSET(i, &ReadFDs))
        {
            retVector.push_back(HandleAndMode(i, READ));
        }
        if (FD_ISSET(i, &WriteFDs))
        {
            retVector.push_back(HandleAndMode(i, WRITE));
        }
        if (FD_ISSET(i, &ExceptFDs))
        {
            retVector.push_back(HandleAndMode(i, EXCEPTION));
        }
    }

    return (retVector);
}