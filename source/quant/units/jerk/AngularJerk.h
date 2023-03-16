#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/QuaternionQuantity.h>


namespace quant::units::jerk
{

    class AngularJerk : public geometry::QuaternionQuantity<AngularJerk>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<AngularJerk>::QuaternionQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const AngularJerk& rhs);

} // namespace quant::units::jerk


namespace quant
{
    using units::jerk::AngularJerk;
} // namespace quant
