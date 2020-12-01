

#ifndef ILRD_RD8586_REACTOR_DETAIL_HPP
#define ILRD_RD8586_REACTOR_DETAIL_HPP

#include <boost/function.hpp> // boost::function
#include <boost/shared_ptr.hpp>
#include <map>    // map
#include <vector> // vector

#include "callback.hpp" // Source and Callback classes

namespace ilrd
{

namespace detail
{

typedef int Handle;

enum MODE
{
    WRITE,
    READ,
    EXCEPTION
};

typedef std::pair< Handle, MODE > HandleAndMode;

typedef Callback< Dispatcher< int > > ReactorCallback;

// wraping the dispatcher object for future change possibility
struct DispatcherClass
{
    Dispatcher< int > m_dispatcher;
};

// helps std::transform to get handle&mode form map functor
class GetHandle
{
public:
    HandleAndMode operator()(
        const std::pair< const HandleAndMode, DispatcherClass >& mapItem) const
    {
        return (mapItem.first);
    }
};

// helps std::foreach to get map item and invoke its callback
class InvokeHandlers
{
public:
    InvokeHandlers(
        std::map< detail::HandleAndMode, detail::DispatcherClass >& map)
        : m_map(map)
    {
    }

    void operator()(detail::HandleAndMode& handle) const
    {
        m_map[handle].m_dispatcher.Notify(handle.first);
    }

private:
    std::map< detail::HandleAndMode, detail::DispatcherClass >& m_map;
};

} // namespace detail

} // namespace ilrd

#endif // ILRD_RD8586_REACTOR_DETAIL_HPP