#pragma once

#include <quant/geometry/AngularIsometricState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/angle/constants.h>
#include <quant/units/position/constants.h>
#include <quant/units/position/forward_declarations.h>

#include <ostream>

namespace quant::units::position
{

    class Orientation : public geometry::AngularIsometricState<Orientation>
    {
    public:
        static Orientation
        radians(geometry::AxisAngle const& aa);
        static Orientation
        radians(Eigen::Quaterniond const& q);
        static Orientation
        degrees(geometry::AxisAngle const& aa);
        static Orientation
        degrees(Eigen::Quaterniond const& q);

        AxisAngle
        to_radians() const;

        AxisAngle
        to_degrees() const;

        std::string
        to_string() const;

        using AngularIsometricState::AngularIsometricState;
    };

    std::ostream&
    operator<<(std::ostream& out, Orientation const& rhs);

}  // namespace quant::units::position
