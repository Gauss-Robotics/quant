#include "Clock.h"

#include <quant/framed_units/time/DateTime.h>
#include <quant/framed_units/time/Duration.h>

#include <chrono>
#include <climits>
#include <string_view>
#include <thread>

namespace quant::framed_units::time::measurement
{

    Clock::Clock(Type clock_type) : _clock_type{clock_type}
    {
        ;
    }

    DateTime
    Clock::now() const
    {
        // Epoch is the frame of reference of the system clock.
        static Duration epoch{units::time::Duration::zero(), {.name = base_frame()}};

        std::chrono::microseconds timestamp_usec;

        switch (_clock_type)
        {
            case Clock::Type::realtime:
            {
                timestamp_usec = std::chrono::time_point_cast<std::chrono::microseconds>(
                                     std::chrono::system_clock::now())
                                     .time_since_epoch();
                break;
            }
            case Clock::Type::monotonic:
            {
                timestamp_usec = std::chrono::time_point_cast<std::chrono::microseconds>(
                                     std::chrono::steady_clock::now())
                                     .time_since_epoch();
                break;
            }
        }

        quant::TimePoint const time_point_since_epoch =
            quant::TimePoint::microseconds(timestamp_usec.count());

        return DateTime::time_point_since_epoch(epoch.enframe(time_point_since_epoch));
    }

    void
    Clock::wait_for(Duration const& duration) const
    {
        std::chrono::microseconds const duration_chrono(
            duration.get_framed_object().to_microseconds());
        std::this_thread::sleep_for(duration_chrono);
    }

    Duration
    Clock::wait_until(DateTime const& date_time) const
    {
        Duration const wait_duration = date_time - now();
        quant::Duration const zero = quant::Duration::zero();

        if (wait_duration > Duration(zero, {.name = "rt_monotonic"}))
        {
            wait_for(wait_duration);
        }

        return wait_duration;
    }

    std::string_view
    Clock::base_frame() const
    {
        return _clock_type == Type::realtime ? "system_clock::epoch_realtime"
                                             : "system_clock::epoch_monotonic";
    }

}  // namespace quant::framed_units::time::measurement
