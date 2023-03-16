#pragma once


#include <functional>

#include <quant/core/clock/StopWatch.h>


namespace quant::time
{

    /**
     * @brief Measures the time this stop watch was inside the current scope.  Takes a lambda as
     * construction parameter (taking an `IceUtil::Time` as parameter), which will be called at
     * destruction (i.e., when the scope was left).
     *
     * Code example:
     *
     * @code
     * {
     *     ScopedStopWatch sw{[](const Duration& duration) {
     *         std::cout << "Operation took " << duration << ".";
     *     }};
     *
     *     long_operation();
     * }
     * @endcode
     */
    class ScopedStopWatch : public StopWatch
    {

    public:
        /**
         * @brief Constructs a `ScopedStopWatch`.
         * @param callback Callback lambda which will be called at destruction with measured time.
         * @param clockType Clock type.
         */
        ScopedStopWatch(std::function<void(const Duration&)> callback,
                        ClockType clockType = ClockType::Virtual);

        /**
         * @brief Destructs the `ScopedStopWatch`.
         */
        ~ScopedStopWatch() override;

    private:
        std::function<void(const Duration&)> callback_;
    };

} // namespace quant::time
