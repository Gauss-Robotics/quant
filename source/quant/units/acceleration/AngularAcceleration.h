#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/QuaternionQuantity.h>


namespace quant::units::acceleration
{

    class AngularAcceleration : public geometry::QuaternionQuantity<AngularAcceleration>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<AngularAcceleration>::QuaternionQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const AngularAcceleration& rhs);

} // namespace quant::units::acceleration


namespace quant
{
    using units::acceleration::AngularAcceleration;
} // namespace quant
