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

    class Distance : geometry::ScalarState<Distance>
    {

    public:
        static Distance
        millimeters(double millimeters)
        {
            return {millimeters};
        }

        static Distance
        meters(geometry::Scalar meters)
        {
            return {meters * constants::m2mm};
        }

        Scalar
        to_millimeters() const
        {
            return {_representation, constants::names::distance, constants::symbols::millimeters};
        }

        // Operators.

    protected:
        using geometry::ScalarState<Distance>::ScalarState;
    };

    std::ostream&
    operator<<(std::ostream& out, Distance const& rhs);

}  // namespace quant::units::distance
