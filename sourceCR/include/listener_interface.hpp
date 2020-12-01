


#ifndef ILRD_RD8586_LISTENER_INTERFACE_HPP
#define ILRD_RD8586_LISTENER_INTERFACE_HPP

#include "reactor_detail.hpp"

namespace ilrd
{

class ListenerInterface
{
public:
    virtual ~ListenerInterface() = 0;

    virtual std::vector< detail::HandleAndMode >
    Listen(const std::vector< detail::HandleAndMode >& handle) = 0;
};

inline ListenerInterface::~ListenerInterface()
{
}

} // namespace ilrd

#endif // ILRD_RD8586_LISTENER_INTERFACE_HPP