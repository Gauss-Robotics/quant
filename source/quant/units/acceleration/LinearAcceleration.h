#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration_constants.h>
#include <quant/units/acceleration_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class LinearAcceleration : public geometry::LinearState<Domain>
    {
    public:
        static LinearAcceleration
        millimeters_per_second_squared(geometry::Vector xyz)
        {
            return {xyz};
        }

        static LinearAcceleration
        meters_per_second_squared(geometry::Vector xyz)
        {
            return {xyz * constants::mpss2mmpss};
        }

        Vector
        to_millimeters_per_second_squared() const
        {
            return {to_vector(),
                    constants::linear_acceleration_name,
                    constants::meters_per_second_squared};
        }

        Vector
        to_meters_per_second_squared() const
        {
            return {to_vector() * constants::mmpss2mpss,
                    constants::linear_acceleration_name,
                    constants::meters_per_second_squared};
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearAcceleration const& rhs)
    {
        return os << rhs.to_millimeters_per_second_squared();
    }

}  // namespace quant::units::acceleration
