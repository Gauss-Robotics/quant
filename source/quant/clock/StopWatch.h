#pragma once


#include <functional>

#include <simox/core/clock/Clock.h>
#include <simox/core/clock/ClockType.h>
#include <simox/core/clock/DateTime.h>
#include <simox/core/units/time/Duration.h>


namespace simox::core::time
{
    /**
     * @brief Measures the passed time between the construction or calling `reset()` and `stop()`.
     *
     * The `StopWatch` uses the system time by default, but it may use the virtual time provided
     * by the time server as well.  Also has a static method `measure()`, which takes a lambda, and
     * returns the time it took to execute that lambda.
     *
     * Code examples:
     *
     * @code
     * // By supplied methods.
     * StopWatch sw;
     *
     * long_operation1();
     *
     * const Duration dur_op1 = sw.lap().sinceLastLap;
     * std::cout << "Operation 1 took " << dur_op1 << ".";
     *
     * long_operation2();
     *
     * const StopWatch::Lap lap = sw.lap();
     * const Duration dur_op2 = lap.sinceLastLap;
     * const Duration dur_all = lap.sinceStart;
     * std::cout << "Operation 2 took " << dur_op2 << ".";
     * std::cout << "All operations took " << dur_all << ".";
     * @endcode
     *
     * @code
     * // By executing a lambda.
     * const Duration duration = StopWatch::measure([&]() {
     *     long_operation();stop
     * });
     * std::cout << "Operation took " << duration << ".";
     * @endcode
     */
    class StopWatch
    {

    public:
        /**
         * @brief Constructs a `StopWatch` and starts it immediately.
         * @param clockType Clock type.
         */
        StopWatch(ClockType clockType = ClockType::Virtual);

        /**
         * @brief Destructs the `StopWatch`.
         */
        virtual ~StopWatch();

        /**
         * @brief Measures the duration needed to execute the given lambda and returns it.
         * @param subjectToMeasure Lambda to be measured
         * @param clockType Clock type.
         * @return Time it took to execute the given lambda.
         */
        static Duration measure(std::function<void(void)> subjectToMeasure,
                                ClockType clockType = ClockType::Virtual);

        struct Lap
        {
            Duration sinceLastLap;
            Duration sinceStart;
        };

        /**
         * @brief Stops the timer and returns the measured duration.
         * @return Duration elapsed since construction or last call of `reset()`.
         */
        Lap lap();

        /**
         * @brief Resets the timer.
         */
        void reset();

        /**
         * @brief Returns the date/time at starting the timer.
         * @return Date/time at starting the timer.
         */
        DateTime startingTime() const;

    private:
        Clock clock_;

        DateTime startingTime_;

        DateTime lastLapTime_;
    };

} // namespace simox::core::time
