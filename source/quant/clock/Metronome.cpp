#include "Metronome.h"

#include <simox/core/clock/Clock.h>


namespace simox::core::time
{

    Metronome::Metronome(const Frequency& targetFrequency, ClockType clockType) :
        clock_{clockType}, targetPeriod_{targetFrequency.toCycleDuration()}
    {
        reset();
    }


    Metronome::Metronome(const Duration& targetPeriod, ClockType clockType) :
        clock_{clockType}, targetPeriod_{targetPeriod}
    {
        reset();
    }


    Metronome::Metronome(const Duration& targetPeriod, const Clock& clock) :
        clock_{clock}, targetPeriod_(targetPeriod)
    {
        reset();
    }


    Duration
    Metronome::waitForNextTick()
    {
        const Duration waitTime = clock_.waitUntil(nextCheckpoint_);
        nextCheckpoint_ += targetPeriod_;
        return waitTime;
    }


    void
    Metronome::reset()
    {
        nextCheckpoint_ = clock_.now() + targetPeriod_;
    }

} // namespace simox::core::time
