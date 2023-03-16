#pragma once


#include <quant/core/clock/Clock.h>
#include <quant/core/clock/DateTime.h>
#include <quant/core/units/time/Duration.h>
#include <quant/core/units/time/Frequency.h>


namespace quant::time
{

    /**
     * @brief Simple rate limiter for use in loops to maintain a certain frequency given a clock.
     *
     * In most cases, it is enough sufficient to construct a rate limiter with a given target
     * duration (or target period). This will then use virtual time. In cases where a specific
     * clock is required, a constructor taking a clock or clock type can be used.
     *
     * Code example:
     *
     * @code
     * using namespace armarx;
     *
     * Metronome m{Frequeny::Hertz(100)}; // For a 100Hz loop.
     * while (condition)
     * {
     *     operation();
     *
     *     const Duration waitingTime = m.waitForNextTick();
     *     std::cout << "We now waited " << waitingTime << ".";
     * }
     * @endcode
     */
    class Metronome
    {

    public:
        Metronome(const Frequency& targetFrequency, ClockType clockType = ClockType::Virtual);

        /**
         * @brief Constructs a new rate limiter with given target period and clock type.
         * @param targetPeriod Period to target for in loops etc.
         * @param clockType Type of clock to use to assess time.
         */
        Metronome(const Duration& targetPeriod, ClockType clockType = ClockType::Virtual);

        /**
         * @brief Constructs a new rate limiter with given target period and clock.
         * @param targetPeriod Period to target for in loops etc.
         * @param clock Clock to use to assess time.
         */
        Metronome(const Duration& targetPeriod, const Clock& clock);

        /**
         * @brief Wait and block until the target period is met.
         * @return The duration the rate limiter waited for. Can be negative if the next deadline
         *         was missed.
         */
        Duration waitForNextTick();

        /**
         * @brief Resets the rate limiter so that the next targetted time point will be in the
         *        current time plus the target period.
         */
        void reset();

    private:
        /**
         * @brief Clock to use to assess time.
         */
        Clock clock_;

        /**
         * @brief Next date/time to target in the next call to wait().
         */
        DateTime nextCheckpoint_;

        /**
         * @brief Period to target.
         */
        const Duration targetPeriod_;
    };

} // namespace quant::time


namespace quant
{
    using core::time::Metronome;
}
