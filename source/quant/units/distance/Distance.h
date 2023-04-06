#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/distance/constants.h>
#include <quant/units/distance_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::distance
{

    class Distance : geometry::ScalarState<Domain>
    {

    public:
        static Distance
        millimeters(double millimeters)
        {
            return {millimeters};
        }

        static Distance
        meters(double meters)
        {
            return {meters * m2mm};
        }

        double
        to_millimeters() const
        {
            return _representation;
        }

        // Operators.

    protected:
        using geometry::ScalarState<Domain>::ScalarState;
    };

    std::ostream&
    operator<<(std::ostream& out, Distance const& rhs);

}  // namespace quant::units::distance
