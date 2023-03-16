#include "ScopedStopWatch.h"

#include <functional>
#include <utility>


namespace quant::time
{

    ScopedStopWatch::ScopedStopWatch(std::function<void(const Duration&)> callback,
                                     ClockType clockType) :
        StopWatch(clockType), callback_{std::move(callback)}
    {
        ;
    }


    ScopedStopWatch::~ScopedStopWatch()
    {
        callback_(lap().sinceStart);
    }

} // namespace quant::time
