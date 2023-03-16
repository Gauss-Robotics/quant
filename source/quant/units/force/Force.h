#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/VectorQuantity.h>


namespace simox::core::units::force
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


    std::ostream& operator<<(std::ostream& out, const Force& rhs);

} // namespace simox::core::units::force


namespace simox
{
    using core::units::force::Force;
} // namespace simox
