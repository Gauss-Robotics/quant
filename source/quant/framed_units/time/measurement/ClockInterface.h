#pragma once

#include <quant/framed_units/time/forward_declarations.h>

#include <string_view>

namespace quant::framed_units::time::measurement
{

    /**
     * @brief Interface to a clock.
     *
     * Used to get the date and time from a specific or wait for certain durations or until certain
     * date/time.
     *
     * @interface ClockInterface
     */
    class ClockInterface
    {
    public:
        /**
         * @brief Current date and time of the clock.
         *
         * @return Current date and time.
         */
        virtual DateTime
        now() const = 0;

        /**
         * @brief Wait for a certain duration.
         *
         * @param duration How long to wait.
         */
        virtual void
        wait_for(Duration const& duration) const = 0;

        /**
         * @brief Wait and block until the given date time is surpassed.
         *
         * @param dateTime Date and time to wait until.
         * @return Actual waiting duration.
         */
        virtual Duration
        wait_until(DateTime const& date_time) const = 0;

        /**
         * @brief Get the base frame of date times returned by now().
         * @return Base frame of this clock.
         */
        virtual std::string_view
        get_base_frame() const = 0;

        /**
         * @brief Default destructor.
         */
        virtual ~ClockInterface() = default;
    };

}  // namespace quant::framed_units::time::measurement
