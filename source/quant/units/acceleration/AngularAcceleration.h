#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/acceleration/constants.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

#include "quant/units/angle/constants.h"

namespace quant::units::acceleration
{

    class AngularAcceleration : public geometry::AngularState<AngularAcceleration>
    {
    public:
        static AngularAcceleration
        radians_per_second_squared(geometry::AxisAngle aa);

        static AngularAcceleration
        radians_per_second_squared(Eigen::Quaterniond const& quaternion);

        AxisAngle
        to_radians_per_second_squared() const;

        static AngularAcceleration
        degrees_per_second_squared(geometry::AxisAngle aa);

        AxisAngle
        to_degrees_per_second_squared() const;

        std::string
        to_string() const;

        using AngularState::AngularState;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs);

}  // namespace quant::units::acceleration
