#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/QuaternionQuantity.h>


namespace simox::core::units::jerk
{

    class AngularJerk : public geometry::QuaternionQuantity<AngularJerk>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<AngularJerk>::QuaternionQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const AngularJerk& rhs);

} // namespace simox::core::units::jerk


namespace simox
{
    using core::units::jerk::AngularJerk;
} // namespace simox
