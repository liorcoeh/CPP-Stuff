

#ifndef ILRD_RD8586_SCHEDULER_DETAIL_HPP
#define ILRD_RD8586_SCHEDULER_DETAIL_HPP

#include <boost/chrono.hpp> // chrono defenitions

namespace ilrd
{

namespace detail
{

typedef boost::chrono::microseconds MicroSecs;
typedef boost::chrono::system_clock::time_point TimePoint;

const int MILLION = 1000000;
const int THOUSAND = 1000;

// Now
// Return: TimePoint object with current system time
inline TimePoint Now()
{
    return (boost::chrono::system_clock::now());
}

// Get Duration
// Receives: timePoint - requested timepoint in future
// Return: MicroSecs object with the duration of time from now to timePoint
inline MicroSecs GetDuration(TimePoint timePoint)
{
    return (boost::chrono::duration_cast< MicroSecs >(timePoint -
                                                      ilrd::detail::Now()));
}

// Microseconds To Seconds
// Receives: microSecs - microseconds to convert
// Return: time_t for microseconds in seconds
inline time_t MicroToSecs(MicroSecs microSecs)
{
    return (microSecs.count() / MILLION);
}

// Microseconds to Nanos
// Receives: microSecs - microseconds to convert
// Return: time_t for microseconds in nanoseconds
inline time_t MicroToNanos(MicroSecs microSecs)
{
    return ((microSecs.count() % MILLION) * THOUSAND);
}

} // namespace detail

} // namespace ilrd

#endif /* ILRD_RD8586_SCHEDULER_DETAIL_HPP */