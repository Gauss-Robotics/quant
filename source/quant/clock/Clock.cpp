#include "Clock.h"

#include <chrono>
#include <climits>
#include <thread>
#include <unistd.h>


namespace simox::core::time
{

    Clock::Clock(ClockType clockType) : clockType_{clockType}
    {
        ;
    }


    DateTime
    Clock::now() const
    {
        std::chrono::microseconds timestamp_usec;

        switch (clockType_)
        {
            case ClockType::Virtual:
            {
                // No time server is set, use realtime instead.
                [[fallthrough]];
            }
            case ClockType::Realtime:
            {
                timestamp_usec = std::chrono::time_point_cast<std::chrono::microseconds>(
                                     std::chrono::system_clock::now())
                                     .time_since_epoch();
                break;
            }
            case ClockType::Monotonic:
            {
                timestamp_usec = std::chrono::time_point_cast<std::chrono::microseconds>(
                                     std::chrono::steady_clock::now())
                                     .time_since_epoch();
                break;
            }
            case ClockType::Unknown:
            {
                throw std::runtime_error{"Cannot asses current time from unknown clock."};
            }
        }

        const std::string hostname = []
        {
            char hostname[HOST_NAME_MAX];
            gethostname(hostname, HOST_NAME_MAX);
            return std::string(hostname);
        }();

        return {Duration::MicroSeconds(timestamp_usec.count()), clockType_, hostname};
    }


    void
    Clock::waitFor(const Duration& duration) const
    {
        std::chrono::microseconds duration_chrono(duration.toMicroSeconds());
        std::this_thread::sleep_for(duration_chrono);
    }


    Duration
    Clock::waitUntil(const DateTime& time) const
    {
        const Duration difference = time - now();
        if (difference.isPositive())
        {
            waitFor(difference);
        }
        return difference;
    }

} // namespace simox::core::time
