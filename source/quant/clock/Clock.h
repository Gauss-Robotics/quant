#pragma once


#include <quant/core/clock/ClockType.h>
#include <quant/core/clock/DateTime.h>
#include <quant/core/units/time/Duration.h>


namespace quant::time
{

    /**
     * @brief Clock to get date/time from a specific clock type or wait for certain durations
     * or until certain date/times in a given clock.
     *
     * In most cases, using the virtual clock is the desired behaviour. The virtual clock reports
     * the current time according to the configured time server, or (as a fallback) the operating
     * systems real time clock. The virtual clock can be accessed through the static methods of
     * this clock.
     *
     * For other cases, i.e., where the actual operating system real time clock is needed
     * (ClockType::Realtime), or a monotonic clock is required (ClockType::Monotonic), a clock
     * with the needed clock type as constructor parameter can be instantiated. The API is then
     * similar to those of the virtual clock using the corresponding non-static member functions.
     */
    class Clock
    {

    public:
        /**
         * @brief Constructs a new clock of given clock type (virtual by default).
         * @param clockType Clock type.
         */
        Clock(ClockType clockType = ClockType::Virtual);

        /**
         * @brief Current date/time of the clock.
         * @return Current date/time.
         */
        DateTime now() const;

        /**
         * @brief Wait for a certain duration.
         * @param duration How long to wait.
         */
        void waitFor(const Duration& duration) const;

        /**
         * @brief Wait and block until the given date/time is surpassed.
         * @param dateTime Date/time to wait until.
         * @return Waiting duration.
         */
        Duration waitUntil(const DateTime& dateTime) const;

    private:
        /**
         * @brief Own clock type.
         */
        ClockType clockType_;
    };


    const static Clock DefaultClock = Clock(ClockType::Virtual);

} // namespace quant::time


namespace quant
{
    using core::time::Clock;
    using core::time::DefaultClock;
} // namespace quant
