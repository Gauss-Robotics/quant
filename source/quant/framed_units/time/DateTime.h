#pragma once

#include <quant/framed_units/time/Duration.h>
#include <quant/framed_units/time/TimePoint.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::framed_units::time
{

    /**
     * @brief Represents a date and time.
     *
     * @todo Do not inherit from TimePoint?
     */
    class DateTime : public TimePoint
    {
    public:
        /**
         * @brief Construct an invalid date time.
         *
         * @todo Add DateTime::Invalid()?
         */
        DateTime() : TimePoint{units::time::TimePoint::microseconds(-1), {}}
        {
            ;
        }

        /**
         * @brief Construct a date time from a time point in the Unix epoch.
         * @param time_point Time point in Unix epoch.
         */
        DateTime(TimePoint const& time_point) : TimePoint{time_point}
        {
            ;
        }

        /**
         * @brief Create a new date time object given a time point relative to epoch.
         *
         * Epoch is defined to be 1970-01-01 00:00:00 (Unix timestamp).
         *
         * @param time_point Time point relative to epoch.
         * @return Date time object.
         */
        static DateTime
        time_point_since_epoch(TimePoint const& time_point)
        {
            return {time_point};
        }

        TimePoint
        to_time_point_since_epoch() const
        {
            return *this;
        }
    };

    /**
     * @brief Translation application operator to apply a duration to a date time object similarly
     * as a time point.
     *
     * @param lhs Duration as translation operator.
     * @param rhs Date time object to be translated.
     * @return Translated date time.
     */
    inline DateTime
    operator+(quant::Duration const& lhs, DateTime const& rhs)
    {
        Duration const lhs_framed{lhs, {.name = rhs.get_base_frame()}};
        TimePoint const rhs_tp = rhs;
        return DateTime::time_point_since_epoch(lhs_framed + rhs_tp);
    }

}  // namespace quant::framed_units::time
