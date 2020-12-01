

#ifndef ILRD_RD8586_REACTOR_LISTENER_HPP
#define ILRD_RD8586_REACTOR_LISTENER_HPP

#include "listener_interface.hpp"

namespace ilrd
{

class ReactorListener : public ListenerInterface
{
public:
    virtual ~ReactorListener();

    virtual std::vector< detail::HandleAndMode >
    Listen(const std::vector< detail::HandleAndMode >& handle);
};

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace ilrd

#endif /* ILRD_RD8586_REACTOR_LISTENER_HPP */
