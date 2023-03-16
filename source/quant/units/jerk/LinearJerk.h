#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/VectorQuantity.h>


namespace simox::core::units::jerk
{

    class LinearJerk : public geometry::VectorQuantity<LinearJerk>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<LinearJerk>::VectorQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const LinearJerk& rhs);

} // namespace simox::core::units::jerk


namespace simox
{
    using core::units::jerk::LinearJerk;
} // namespace simox
