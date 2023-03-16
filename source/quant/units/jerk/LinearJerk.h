#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/VectorQuantity.h>


namespace quant::units::jerk
{

    class LinearJerk : public geometry::VectorQuantity<LinearJerk>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<LinearJerk>::VectorQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const LinearJerk& rhs);

} // namespace quant::units::jerk


namespace quant
{
    using units::jerk::LinearJerk;
} // namespace quant
