#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/VectorQuantity.h>


namespace quant::units::acceleration
{

    class LinearAcceleration : public geometry::VectorQuantity<LinearAcceleration>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<LinearAcceleration>::VectorQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const LinearAcceleration& rhs);

} // namespace quant::units::acceleration


namespace quant
{
    using units::acceleration::LinearAcceleration;
} // namespace quant
