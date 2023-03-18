#pragma once


#include <quant/geometry/VectorQuantity.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::force
{

    class Force : public geometry::VectorQuantity<Force>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<Force>::VectorQuantity;

        static Force
        Zero()
        {
            return Origin();
        }

        static Force
        Newton(Vector xyz)
        {
            return {xyz.x, xyz.y, xyz.z};
        }
    };

    std::ostream& operator<<(std::ostream& out, Force const& rhs);

}  // namespace quant::units::force

namespace quant
{

    using units::force::Force;

}  // namespace quant
