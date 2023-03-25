#pragma once

#include <quant/geometry/ScalarQuantity.h>
#include <quant/units/distance_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::distance
{

    constexpr double m2mm = 1'000;

    class Distance : geometry::ScalarQuantity<Domain>
    {

    public:
        static Distance
        MilliMeters(double milliMeters)
        {
            return {milliMeters};
        }

        static Distance
        Meters(double meters)
        {
            return {meters * m2mm};
        }

        std::string
        toString() const;

        double
        toMilliMeters() const
        {
            return representation_;
        }

        // Operators.

    protected:
        using geometry::ScalarQuantity<Domain>::ScalarQuantity;  // TODO(dreher): Remove? All scalar
                                                                 // quantities
    };

    std::ostream&
    operator<<(std::ostream& out, Distance const& rhs);

}  // namespace quant::units::distance

namespace quant
{
    using units::distance::Distance;
}  // namespace quant
