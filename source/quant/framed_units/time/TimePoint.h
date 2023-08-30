#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/time/forward_declarations.h>
#include <quant/units/time/TimePoint.h>

namespace quant::framed_units::time
{

    class TimePoint : public Framed<units::time::TimePoint>
    {

    public:
        TimePoint(units::time::TimePoint const& t, FrameData const& frame) :
            Framed<units::time::TimePoint>(t, frame)
        {
            ;
        }
    };

}  // namespace quant::framed_units::time
