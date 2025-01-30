#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/speed/Speed.h>
#include <quant/units/velocity/forward_declarations.h>

#include "forward_declarations.h"

namespace quant::units::speed
{
    class SpeedDifference : public geometry::Difference<Speed>
    {
    public:
        SpeedDifference(LinearVelocityDifference const& vel);

        static SpeedDifference
        millimeters_per_second(geometry::Scalar millimeters_per_second);

        static SpeedDifference
        meters_per_second(geometry::Scalar meters_per_second);

        Scalar
        to_millimeters_per_second() const;

        Scalar
        to_meters_per_second() const;

        using Difference::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& out, SpeedDifference const& rhs)
    {
        return out << rhs.to_millimeters_per_second();
    }
}  // namespace quant::units::speed