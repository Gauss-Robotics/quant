#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration/constants.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class LinearAcceleration : public geometry::LinearState<LinearAcceleration>
    {
    public:
        static LinearAcceleration
        millimeters_per_second_squared(const geometry::Vector& xyz)
        {
            return {xyz};
        }

        static LinearAcceleration
        millimeters_per_second_squared(const Eigen::Vector3d& xyz)
        {
            return {xyz};
        }

        static LinearAcceleration
        meters_per_second_squared(const geometry::Vector& xyz)
        {
            return {xyz * constants::mpss2mmpss};
        }

        static LinearAcceleration
        meters_per_second_squared(const Eigen::Vector3d& xyz)
        {
            return {xyz * constants::mpss2mmpss};
        }

        Vector
        to_millimeters_per_second_squared() const
        {
            return {to_vector(),
                    constants::names::linear_acceleration,
                    constants::symbols::meters_per_second_squared};
        }

        Vector
        to_meters_per_second_squared() const
        {
            return {to_vector() * constants::mmpss2mpss,
                    constants::names::linear_acceleration,
                    constants::symbols::meters_per_second_squared};
        }

        using geometry::LinearState<LinearAcceleration>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearAcceleration const& rhs)
    {
        return os << rhs.to_millimeters_per_second_squared();
    }

}  // namespace quant::units::acceleration
