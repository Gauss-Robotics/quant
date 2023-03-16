#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/VectorQuantity.h>


namespace simox::core::units::acceleration
{

    class LinearAcceleration : public geometry::VectorQuantity<LinearAcceleration>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<LinearAcceleration>::VectorQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const LinearAcceleration& rhs);

} // namespace simox::core::units::acceleration


namespace simox
{
    using core::units::acceleration::LinearAcceleration;
} // namespace simox
