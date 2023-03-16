#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/QuaternionQuantity.h>


namespace simox::core::units::acceleration
{

    class AngularAcceleration : public geometry::QuaternionQuantity<AngularAcceleration>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<AngularAcceleration>::QuaternionQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const AngularAcceleration& rhs);

} // namespace simox::core::units::acceleration


namespace simox
{
    using core::units::acceleration::AngularAcceleration;
} // namespace simox
