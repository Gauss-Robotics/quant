#pragma once

#include <quant/geometry/T3TangentState.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration/constants.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class LinearAcceleration : public geometry::T3TangentState<LinearAcceleration>
    {
    public:
        static LinearAcceleration
        millimeters_per_second_squared(geometry::Vector const& xyz);

        static LinearAcceleration
        meters_per_second_squared(geometry::Vector const& xyz);

        Vector
        to_millimeters_per_second_squared() const;

        Vector
        to_meters_per_second_squared() const;

        std::string
        to_string() const;

        using T3TangentState<LinearAcceleration>::T3TangentState;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearAcceleration const& rhs);

}  // namespace quant::units::acceleration
