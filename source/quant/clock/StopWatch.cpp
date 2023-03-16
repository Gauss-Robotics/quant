#include "StopWatch.h"

#include <exception>


namespace simox::core::time
{

    StopWatch::StopWatch(ClockType clockType) :
        clock_{clockType}, startingTime_{clock_.now()}, lastLapTime_{startingTime_}
    {
        ;
    }


    StopWatch::~StopWatch()
    {
        ;
    }


    Duration
    StopWatch::measure(std::function<void(void)> subjectToMeasure, ClockType clockType)
    {
        StopWatch sw{clockType};
        subjectToMeasure();
        return sw.lap().sinceStart;
    }


    StopWatch::Lap
    StopWatch::lap()
    {
        const DateTime now = clock_.now();
        const Duration sinceLastLap = now - lastLapTime_;
        const Duration sinceStart = now - startingTime_;
        lastLapTime_ = now;

        return {.sinceLastLap = sinceLastLap, .sinceStart = sinceStart};
    }


    void
    StopWatch::reset()
    {
        startingTime_ = clock_.now();
        lastLapTime_ = startingTime_;
    }


    DateTime
    StopWatch::startingTime() const
    {
        return startingTime_;
    }

} // namespace simox::core::time
