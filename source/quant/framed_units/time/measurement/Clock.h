#pragma once

#include <quant/framed_units/time/DateTime.h>
#include <quant/framed_units/time/forward_declarations.h>
#include <quant/framed_units/time/measurement/ClockInterface.h>

namespace quant::framed_units::time::measurement
{

    /**
     * @brief Basic system clock implementation with realtime and monotonic modes.
     *
     * This clock is implemented with the basic system clock, and exposes system clock modes with
     * Clock::Type.  The waiting operations wait_for() and wait_until() are implemented by
     * suspending the thread.  Due to scheduling limitations of the operating system, the actual
     * waiting times might thus be longer than the requested times.
     */
    class Clock : public ClockInterface
    {
    public:
        /**
         * @brief System clock type.
         */
        enum class Type
        {
            /**
             * @brief Synchronized realtime clock.
             *
             * A clock in this mode is potentially time-adjusted and synchronized with an external
             * time server. This means that a call to now() might return a date time that is
             * seemingly in the past relative to earlier calls to now() using the same clock object
             * if a time synchronization occurred within subsequent calls.
             */
            realtime,

            /**
             * @brief Monotonic local system clock.
             *
             * A clock in this mode is using the relative, local on-board system clock, which will
             * not be time-adjusted (thus "monotonically" incrementing).  This means that time jumps
             * as with Type::realtime will not happen.  While this is a positive property when
             * accessing durations, it is also prone to drift on a larger scale.
             */
            monotonic
        };

        /**
         * @brief Constructs a new clock of given clock type (virtual by default).
         *
         * @param clockType Clock type.
         */
        Clock(Type clockType = Type::realtime);

        DateTime
        now() const override;

        void
        wait_for(Duration const& duration) const override;

        Duration
        wait_until(DateTime const& date_time) const override;

        std::string_view
        base_frame() const override;

        ~Clock() override = default;

    private:
        /**
         * @brief Own clock type.
         */
        Type const _clock_type;
    };

    /**
     * @brief General default system clock using the "realtime" system clock mode.
     */
    const static Clock default_clock = Clock(Clock::Type::realtime);

}  // namespace quant::framed_units::time::measurement
