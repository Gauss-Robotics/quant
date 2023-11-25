#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/time/forward_declarations.h>
#include <quant/units/Scalar.h>
#include <quant/units/time/TimePoint.h>

namespace quant::framed_units::time
{

    class TimePoint : public Framed<units::time::TimePoint>
    {

    public:
        using Framed<units::time::TimePoint>::Framed;

        TimePoint(units::time::TimePoint const& t, FrameData const& frame) :
            Framed<units::time::TimePoint>(t, frame)
        {
            ;
        }

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        units::Scalar
        to_microseconds() const
        {
            return get_framed_object().to_microseconds();
        }
    };

}  // namespace quant::framed_units::time
